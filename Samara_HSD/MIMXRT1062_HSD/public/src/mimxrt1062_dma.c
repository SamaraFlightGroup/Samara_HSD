#include "mimxrt1062_dma.h"

#define DMA_NUM_CHANNELS 32
#define DMA_UNUSED_MASK  0xFFFFFFFF

typedef enum
{
    DMA_ATTR_SIZE_1_BYTE  = 0x0,
    DMA_ATTR_SIZE_2_BYTE  = 0x1,
    DMA_ATTR_SIZE_4_BYTE  = 0x2,
    DMA_ATTR_SIZE_8_BYTE  = 0x3,
    DMA_ATTR_SIZE_RESERV  = 0x4,
    DMA_ATTR_SIZE_32_BYTE = 0x5,
    DMA_ATTR_SIZE_INVALID = 0xF
} dma_attr_size_t;

sal_dma_obj_s* dma_objs[DMA_NUM_CHANNELS];

static uint32_t dma_available_msk = DMA_UNUSED_MASK;

static bool     dma_initialized       = false;

// Interface Functions Forward Declarations
static sal_config_error_mask_t     dma_request              (sal_dma_obj_s* dma_obj);
static void                        dma_release              (sal_dma_obj_s* dma_obj);
static sal_config_error_mask_t     dma_set_config           (sal_dma_obj_s* dma_obj, sal_dma_config_s dma_config);
static uint32_t                    dma_get_error_status     (sal_dma_obj_s* dma_obj);
static void                        dma_start_transfer       (sal_dma_obj_s* dma_obj);

// ISR function
static void     dma_isr();

// Helper Function Forward Delcarations
static inline unsigned int                    dma_obj_to_num             (sal_dma_obj_s* dma_obj);
static        dma_attr_size_t                 dma_byte_to_attr_size      (unsigned int   size   );

static        void                            dma_suspend_hw_req         (sal_dma_obj_s* dma_obj);
static inline bool                            dma_active                 (sal_dma_obj_s* dma_obj);

static        sal_config_error_mask_t         dma_check_transfer_config  (sal_dma_obj_s* dma_obj);
static        sal_config_error_mask_t         dma_check_transfer_config  (sal_dma_obj_s* dma_obj);
static        sal_config_error_mask_t         dma_check_transfer_config  (sal_dma_obj_s* dma_obj);

static        int                             dma_reserve                ();
static        void                            dma_init                   ();

static        sal_config_error_mask_t         dma_set_transfer_config    (sal_dma_obj_s* dma_obj, sal_dma_transfer_config_s dma_transfer_config);
static        sal_config_error_mask_t         dma_set_channel_config     (sal_dma_obj_s* dma_obj, sal_dma_channel_config_s dma_channel_config);
static        sal_config_error_mask_t         dma_set_irq_config         (sal_dma_obj_s* dma_obj, sal_irq_config_s dma_irq_config);

// setup DMA interface
const struct sal_dma_interface dma =
{
    dma_request,
    dma_release,
    dma_set_config,
    dma_get_error_status,
    dma_start_transfer
};


static sal_config_error_mask_t dma_request(sal_dma_obj_s* dma_obj)
{
    int dma_num = dma_reserve();
    if(dma_num < 0)
    {
        return SAL_CONFIG_ERROR_HW_UNAVAILABLE_MASK;
    }

    dma_init();

    memset(dma_obj, 0, sizeof(*dma_obj));

    dma_obj->mem_map_periph.perip_num   = dma_num;
    dma_obj->mem_map_periph.periph_addr = (unsigned int)DMA0;

    dma_objs[dma_num] = dma_obj;

    return SAL_CONFIG_ERROR_NONE;
}

/**
 * @brief
 *
 * @param dma_obj
 */
static void dma_release(sal_dma_obj_s* dma_obj)
{
    unsigned int dma_num = dma_obj_to_num(dma_obj);

    dma_suspend_hw_req(dma_obj);

    dma_available_msk |= 1 << dma_num;

    if(dma_available_msk == DMA_UNUSED_MASK)
    {
        CCM->CCGR5 &= ~CCM_CCGR5_CG3_MASK;
        dma_initialized = false;
    }

}

static sal_config_error_mask_t dma_set_config(sal_dma_obj_s* dma_obj, sal_dma_config_s dma_config)
{
    sal_config_error_mask_t ret_val = false;

    dma_suspend_hw_req(dma_obj);
    while(dma_active(dma_obj))
    {
        __NOP();
    }

    ret_val |= dma_set_transfer_config(dma_obj, dma_config.transfer);
    ret_val |= dma_set_irq_config     (dma_obj, dma_config.irq);
    ret_val |= dma_set_channel_config (dma_obj, dma_config.channel);

    return ret_val;
}

static uint32_t dma_get_error_status(sal_dma_obj_s* dma_obj)
{
    return 0xFFFFFFFF;
}

static void dma_start_transfer(sal_dma_obj_s* dma_obj)
{
    unsigned int dma_num = dma_obj_to_num(dma_obj);

    DMA0->TCD[dma_num].CSR |= DMA_CSR_START_MASK;
}

static void dma_isr()
{
    uint32_t error_status = DMA0->ES;
    unsigned int error_num = (error_status & DMA_ES_ERRCHN_MASK) >> DMA_ES_ERRCHN_SHIFT;

    const uint32_t CONFIG_ERROR_MASK =
        DMA_ES_SGE_MASK | DMA_ES_NCE_MASK | DMA_ES_DOE_MASK |
        DMA_ES_DAE_MASK | DMA_ES_SOE_MASK | DMA_ES_SAE_MASK ;

    const uint32_t SRC_BUS_ERROR_MASK = DMA_ES_SBE_MASK;

    const uint32_t DST_BUS_ERROR_MASK = DMA_ES_DBE_MASK;

    if(error_status & CONFIG_ERROR_MASK)
    {
        dma_objs[error_num]->error_status.error_mask |= SAL_DMA_ERROR_CONFIG_MASK;
    }

    if(error_status & SRC_BUS_ERROR_MASK)
    {
        dma_objs[error_num]->error_status.error_mask |= SAL_DMA_ERROR_SRC_BUS_MASK;
    }

    if(error_status & DST_BUS_ERROR_MASK)
    {
        dma_objs[error_num]->error_status.error_mask |= SAL_DMA_ERROR_DST_BUS_MASK;
    }

    for(int i = 0; i < DMA_NUM_CHANNELS; i++)
    {
        uint32_t dma_mask = 1 << i;
        if(DMA0->INT & dma_mask)
        {
            dma_objs[i]->config.irq.irq_callback();
            DMA0->CINT |= dma_mask;
        }
    }
}

/**
 * @brief
 *
 * @param dma_obj
 * @return unsigned int
 */
static inline unsigned int dma_obj_to_num(sal_dma_obj_s* dma_obj)
{
    return dma_obj->mem_map_periph.perip_num;
}

/**
 * @brief
 *
 * @param size
 * @return unsigned int
 */
static dma_attr_size_t dma_byte_to_attr_size(unsigned int size)
{
    switch (size)
    {
        case 1:
            return DMA_ATTR_SIZE_1_BYTE;

        case 2:
            return DMA_ATTR_SIZE_2_BYTE;

        case 4:
            return DMA_ATTR_SIZE_4_BYTE;

        case 8:
            return DMA_ATTR_SIZE_8_BYTE;

        case 32:
            return DMA_ATTR_SIZE_32_BYTE;

        default:
            return DMA_ATTR_SIZE_INVALID;
    }
}
/**
 * @brief
 *
 * @param dma_num
 */
static void dma_suspend_hw_req(sal_dma_obj_s* dma_obj)
{
    unsigned int dma_num = dma_obj_to_num(dma_obj);
    // While there is a hardware request
    while(DMA0->HRS & (1 << dma_num))
    {
        __NOP();
    }

    // Disable ability for Hardware Requests
    DMA0->CERQ |= DMA_CERQ_CERQ(dma_num);

    // Clear mux channel configuration
    DMAMUX->CHCFG[dma_num] = 0;

    while(DMA0->TCD[dma_num].CSR & DMA_CSR_ACTIVE_MASK)
    {
        __NOP();
    }
}

/**
 * @brief
 *
 * @param dma_num
 * @return true
 * @return false
 */
static inline bool dma_active(sal_dma_obj_s* dma_obj)
{
    return (bool)(DMA0->TCD[dma_obj_to_num(dma_obj)].CSR & DMA_CSR_ACTIVE_MASK);
}

/**
 * @brief
 *
 * @param dma_obj
 * @return true
 * @return false
 */
static sal_config_error_mask_t dma_check_transfer_config (sal_dma_obj_s* dma_obj)
{
    sal_config_error_mask_t ret_val = SAL_CONFIG_ERROR_NONE;
    if( (dma_obj->config.transfer.src_addr_offset > INT16_MAX) || (dma_obj->config.transfer.src_addr_offset < INT16_MIN) )
    {
        ret_val |= SAL_CONFIG_ERROR_INVALID_CONFIG_MASK;
    }
    else if( (dma_obj->config.transfer.dst_addr_offset > INT16_MAX) || (dma_obj->config.transfer.dst_addr_offset < INT16_MIN) )
    {
        ret_val |= SAL_CONFIG_ERROR_INVALID_CONFIG_MASK;
    }

    return ret_val;
}

static sal_config_error_mask_t dma_check_irq_config(sal_dma_obj_s* dma_obj)
{
    sal_config_error_mask_t ret_val = SAL_CONFIG_ERROR_NONE;

    if( (dma_obj->config.irq.irq_trig != SAL_DMA_IRQ_TRIG_LOOP_END) && (dma_obj->config.irq.irq_trig != SAL_DMA_IRQ_TRIG_NONE) )
    {
        ret_val |= SAL_CONFIG_ERROR_INVALID_IRQ_MASK;
    }
    else if( (dma_obj->config.irq.irq_trig != SAL_DMA_IRQ_TRIG_NONE) && (dma_obj->config.irq.irq_callback == NULL) )
    {
        ret_val |= SAL_CONFIG_ERROR_INVALID_IRQ_MASK;
    }

    return ret_val;
}

static sal_config_error_mask_t dma_check_channel_config(sal_dma_obj_s* dma_obj)
{
    sal_config_error_mask_t ret_val = SAL_CONFIG_ERROR_NONE;
    const unsigned int MAX_CHANNEL_SOURCE = DMAMUX_CHCFG_SOURCE_MASK >> DMAMUX_CHCFG_SOURCE_SHIFT;

    if(dma_obj->config.channel.dma_channel_src > MAX_CHANNEL_SOURCE)
    {
        ret_val |= SAL_CONFIG_ERROR_INVALID_MUX_MASK;
    }

    return ret_val;
}

static int dma_reserve()
{
    int i = 31;

    for(; i >= 0; i--)
    {
        if(dma_available_msk & (1 << i))
        {
            break;
        }
    }

    return i;
}

/**
 * @brief
 *
 */
static void dma_init()
{
    // Enable the dma hclk and ipg clock
    if(dma_initialized)
    {
        return;
    }

    // Enable the clock for dma
    CCM->CCGR5 |= CCM_CCGR5_CG3_MASK;

    // Enable priority for channels 16-31 which use round robin between them
    DMA0->CR =
        DMA_CR_GRP1PRI_MASK | DMA_CR_GRP0PRI(0) | DMA_CR_ERGA(0) | DMA_CR_ERCA(1);

    dma_initialized = true;
}

static sal_config_error_mask_t dma_set_transfer_config(sal_dma_obj_s* dma_obj, sal_dma_transfer_config_s dma_transfer_config)
{
    unsigned int dma_num = dma_obj_to_num(dma_obj);

    sal_config_error_mask_t ret_val = SAL_CONFIG_ERROR_NONE;

    dma_attr_size_t attr_src_size = dma_byte_to_attr_size(dma_transfer_config.src_read_size);
    dma_attr_size_t attr_dst_size = dma_byte_to_attr_size(dma_transfer_config.dst_write_size);

    if( (attr_dst_size == DMA_ATTR_SIZE_INVALID) || (attr_dst_size == DMA_ATTR_SIZE_INVALID) )
    {
        ret_val |= SAL_CONFIG_ERROR_INVALID_CONFIG_MASK;
    }
    ret_val |= dma_check_transfer_config(dma_obj);

    // Update dma_obj
    dma_obj->config.transfer = dma_transfer_config;

    DMA0->TCD[dma_num].SADDR = dma_transfer_config.src_addr;
    DMA0->TCD[dma_num].SOFF  = (int16_t)dma_transfer_config.src_addr_offset;
    DMA0->TCD[dma_num].SLAST = dma_transfer_config.src_loop_end_offset;

    DMA0->TCD[dma_num].ATTR  =
        DMA_ATTR_SMOD(dma_transfer_config.src_addr_mod_log2) | DMA_ATTR_SSIZE(attr_src_size) |
        DMA_ATTR_DMOD(dma_transfer_config.dst_addr_mod_log2) | DMA_ATTR_DSIZE(attr_dst_size);

    DMA0->TCD[dma_num].NBYTES_MLNO = DMA_NBYTES_MLNO_NBYTES(dma_transfer_config.loop_transfer_size);

    DMA0->TCD[dma_num].DADDR     = dma_transfer_config.dst_addr;
    DMA0->TCD[dma_num].DOFF      = (int16_t)dma_transfer_config.dst_addr_offset;
    DMA0->TCD[dma_num].DLAST_SGA = dma_transfer_config.dst_loop_end_offset;

    DMA0->TCD[dma_num].BITER_ELINKNO = dma_transfer_config.loop_count;
    DMA0->TCD[dma_num].CITER_ELINKNO = dma_transfer_config.loop_count;

    return ret_val;
}

static sal_config_error_mask_t dma_set_channel_config(sal_dma_obj_s* dma_obj, sal_dma_channel_config_s dma_channel_config)
{
    unsigned int dma_num = dma_obj_to_num(dma_obj);

    sal_config_error_mask_t ret_val = dma_check_channel_config(dma_obj);

    // Update dma_obj
    dma_obj->config.channel = dma_channel_config;

    // Configure channel
    DMAMUX->CHCFG[dma_num] =
        DMAMUX_CHCFG_ENBL(dma_channel_config.channel_enable) | DMAMUX_CHCFG_TRIG(dma_channel_config.pit_trig_en)       |
        DMAMUX_CHCFG_A_ON(dma_channel_config.always_en)      | DMAMUX_CHCFG_SOURCE(dma_channel_config.dma_channel_src) ;

    // Enable Hardware requests if channel_enable == 1
    DMA0->ERQ |= DMA_ERQ_ERQ0(dma_channel_config.channel_enable) << dma_num;

    return ret_val;
}

static sal_config_error_mask_t dma_set_irq_config(sal_dma_obj_s* dma_obj, sal_irq_config_s irq_config)
{
    unsigned int dma_num = dma_obj_to_num(dma_obj);
    IRQn_Type irq_num = (dma_num % 16) + DMA0_DMA16_IRQn;

    sal_config_error_mask_t ret_val = dma_check_irq_config(dma_obj);

    // Update dma object
    dma_obj->config.irq = irq_config;

    // Create config with no interrupts
    uint32_t tcd_ctl_config = DMA0->TCD[dma_num].CSR & ~(DMA_CSR_INTMAJOR_MASK | DMA_CSR_INTHALF_MASK);

    switch (irq_config.irq_trig)
    {
        // Enable end of Major loop interrupts
        case SAL_DMA_IRQ_TRIG_LOOP_END:
            tcd_ctl_config |= DMA_CSR_INTMAJOR_MASK;
            break;

        // Set no interrupt trigger
        case SAL_DMA_IRQ_TRIG_NONE:
        // Fallthrough
        default:
            break;
    }

    // Set active interrupt type
    DMA0->TCD[dma_num].CSR = tcd_ctl_config;

    // Enable interrupt on error
    DMA0->SEEI             = DMA_SEEI_SEEI(dma_num);

    NVIC_SetPriorityGrouping(0);
    NVIC_SetVector(irq_num, (unsigned int)dma_isr);
    NVIC_SetPriority(irq_num, irq_config.irq_priority);
    NVIC_EnableIRQ(irq_num);

    __enable_irq();

    return ret_val;
}