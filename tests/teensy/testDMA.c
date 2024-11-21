#include "mimxrt1062_usart.h"

int main()
{
    sal_dma_obj_s dma_obj;
    GPIO2->GDIR   |= 1 << 3;
    GPIO2->DR_CLEAR |= 1 << 3;

    if(dma.request(&dma_obj) != SAL_CONFIG_ERROR_NONE)
    {
        return 1;
    }

    sal_dma_config_s config;
    volatile uint32_t         src = 0x12345678;
    volatile uint32_t         dst = 0;

    config.channel.channel_enable = false;

    config.irq.irq_trig = SAL_DMA_IRQ_TRIG_NONE;

    config.transfer.src_addr = &src;
    config.transfer.src_addr_offset = sizeof(uint32_t);
    config.transfer.src_read_size = 4;
    config.transfer.src_loop_end_offset = -sizeof(uint32_t);

    config.transfer.dst_addr = &dst;
    config.transfer.dst_addr_offset = sizeof(uint32_t);
    config.transfer.dst_write_size = 4;
    config.transfer.dst_loop_end_offset = -sizeof(uint32_t);

    config.transfer.loop_count = 1;
    config.transfer.loop_transfer_size = sizeof(uint32_t);

    if(dma.set_config(&dma_obj, config) != SAL_CONFIG_ERROR_NONE)
    {
        return 1;
    }

    dma.start_transfer(&dma_obj);

    dma.release(&dma_obj);

    for(int i =0; i < 0xFFFFFF; i++)
    {
        __NOP();
    }
    while(src == dst)
    {
        GPIO2->DR_TOGGLE |= 1 << 3;
        for(int i =0; i < 0xFFFFFF; i++)
        {
            __NOP();
        }
    }

    GPIO2->DR_SET |= 1 << 3;

    return 0;
}