#include "UART.h"

static LPUART_Type* peripheralToAddress[UART_NUM_PERIPHERALS] = { NULL, LPUART1, LPUART2, LPUART3, LPUART4, LPUART5, LPUART6, LPUART7, LPUART8 };
static const IRQn_Type peripheralToIRQ[UART_NUM_PERIPHERALS] = LPUART_RX_TX_IRQS;

static uint8_t txData[UART_NUM_PERIPHERALS][255];
static uint8_t rxData[UART_NUM_PERIPHERALS][255];
static uint8_t txPutIndex[UART_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t txGetIndex[UART_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t rxPutIndex[UART_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t rxGetIndex[UART_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static void LPUART_IRQHandler(UART_Peripheral_t uartNum);
static inline uint8_t getTXFIFOCount(LPUART_Type* uart);
static inline uint8_t getRXFIFOCount(LPUART_Type* uart);
static uint16_t getDivider(UART_Config_t* config);

static bool init = false;
void UART_Init()
{
    if(init)
    {
        return;
    }
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CSCDR1 &= ~CCM_CSCDR1_UART_CLK_PODF_MASK;

    IOMUXC->SW_MUX_CTL_PAD[kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_12] = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(1); // TX
    IOMUXC->SW_MUX_CTL_PAD[kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_13] = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(1); // RX
    //IOMUXC->SELECT_INPUT[kIOMUXC_LPUART5_TX_SELECT_INPUT] = 1;
    IOMUXC->SELECT_INPUT[kIOMUXC_LPUART5_RX_SELECT_INPUT] = 1;
    init = true;
}
static bool printfInit = false;
void printf_Init()
{
    if(printfInit)
    {
        return;
    }
    UART_Init();

    UART_Config_t config;
    UART_GetDefaultConfig(&config, UART5, 115200);
    UART_SetConfig(&config);
    printfInit = true;
}

void UART_GetDefaultConfig(UART_Config_t* config, UART_Peripheral_t uartNum, uint32_t baudRate)
{
    config->uart = peripheralToAddress[uartNum];
    config->uartNum = uartNum;

    config->tenBitMode = false;
    config->overSamplingRatio = 16;
    config->bothEdgeSampling = false;
    config->MSBFirst = false;
    config->txInvert = false;
    config->rxInvert = false;
    config->parity = UART_NOPARITY;

    config->baudRate = baudRate;
}

void UART_GetConfig(UART_Config_t* config, UART_Peripheral_t uartNum, uint32_t baudRate, bool tenBitMode, uint8_t overSamplingRatio, bool bothEdgeSampling, bool MSBFirst, bool txInvert, bool rxInvert, UART_Parity_t parity, bool twoStopBits)
{
    config->uart = peripheralToAddress[uartNum];
    config->uartNum = uartNum;

    config->tenBitMode = tenBitMode;
    config->overSamplingRatio = overSamplingRatio;
    config->bothEdgeSampling = bothEdgeSampling;
    config->MSBFirst = MSBFirst;
    config->txInvert = txInvert;
    config->rxInvert = rxInvert;
    config->parity = parity;

    config->baudRate = baudRate;
}

void UART_SetConfig(UART_Config_t* config)
{
    config->uart->GLOBAL = LPUART_GLOBAL_RST(1);
    config->uart->GLOBAL = LPUART_GLOBAL_RST(0);

    uint16_t divider = getDivider(config);

    config->uart->PINCFG = 0;

    config->uart->BAUD = LPUART_BAUD_M10(config->tenBitMode) | LPUART_BAUD_OSR(config->overSamplingRatio - 1) |
        LPUART_BAUD_BOTHEDGE(config->bothEdgeSampling) | LPUART_BAUD_SBR(divider);

    config->uart->CTRL = LPUART_CTRL_TXINV(config->txInvert) | LPUART_CTRL_PE(config->parity) |
        LPUART_CTRL_PT(config->parity >> 1) | LPUART_CTRL_RIE_MASK;

    config->uart->STAT = LPUART_STAT_LBKDIF_MASK | LPUART_STAT_RXEDGIF_MASK | LPUART_STAT_MSBF(config->MSBFirst) |
        LPUART_STAT_RXINV(config->rxInvert) | LPUART_STAT_IDLE_MASK | LPUART_STAT_OR_MASK |
        LPUART_STAT_NF_MASK | LPUART_STAT_FE_MASK | LPUART_STAT_PF_MASK |
        LPUART_STAT_MA1F_MASK | LPUART_STAT_MA2F_MASK;

    config->uart->FIFO = LPUART_FIFO_TXFE_MASK | LPUART_FIFO_RXFE_MASK;
    config->uart->FIFO |= LPUART_FIFO_TXFLUSH_MASK | LPUART_FIFO_RXFLUSH_MASK;

    config->uart->WATER = LPUART_WATER_TXWATER(0) | LPUART_WATER_RXWATER(0);

    config->uart->CTRL |= LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK;
    NVIC_EnableIRQ(peripheralToIRQ[config->uartNum]);
    __enable_irq();
}

void UART_Write(UART_Peripheral_t uartNum, uint8_t data)
{
    LPUART_Type* uart = peripheralToAddress[uartNum];
    txData[uartNum][txPutIndex[uartNum]] = data;
    txPutIndex[uartNum]++;
    uart->CTRL |= LPUART_CTRL_TIE_MASK;
}

void UART_WriteBytes(UART_Peripheral_t uartNum, uint8_t* data, uint8_t size)
{
    LPUART_Type* uart = peripheralToAddress[uartNum];
    for (uint8_t i = 0; i < size; i++)
    {
        txData[uartNum][txPutIndex[uartNum]] = data[i];
        txPutIndex[uartNum]++;
    }
    uart->CTRL |= LPUART_CTRL_TIE_MASK;
}

uint8_t UART_Read(UART_Peripheral_t uartNum)
{
    uint8_t data = 0xEE;

    if (UART_IsDataAvailable(uartNum))
    {
        data = rxData[uartNum][rxGetIndex[uartNum]];
        rxGetIndex[uartNum]++;
    }
    return data;
}

void UART_ReadBytes(UART_Peripheral_t uartNum, uint8_t* data, uint8_t* size)
{
    if (UART_GetBytesAvailable(uartNum) < *size)
    {
        *size = UART_GetBytesAvailable(uartNum);
    }

    for (uint8_t i = 0; i < *size; i++)
    {
        data[i] = rxData[uartNum][rxGetIndex[uartNum]];
        rxGetIndex[uartNum]++;
    }
}

bool UART_IsDataAvailable(UART_Peripheral_t uartNum)
{
    return rxGetIndex[uartNum] != rxPutIndex[uartNum];
}

uint8_t UART_GetBytesAvailable(UART_Peripheral_t uartNum)
{
    if (rxGetIndex[uartNum] < rxPutIndex[uartNum])
    {
        return rxPutIndex[uartNum] - rxGetIndex[uartNum];
    }
    else if (rxGetIndex[uartNum] > rxPutIndex[uartNum])
    {
        return 255 - rxGetIndex[uartNum] + rxPutIndex[uartNum] + 1;
    }
    else
    {
        return 0;
    }
}

inline void UART1_Write(uint8_t data) { UART_Write(UART1, data); }
inline void UART2_Write(uint8_t data) { UART_Write(UART2, data); }
inline void UART3_Write(uint8_t data) { UART_Write(UART3, data); }
inline void UART4_Write(uint8_t data) { UART_Write(UART4, data); }
inline void UART5_Write(uint8_t data) { UART_Write(UART5, data); }
inline void UART6_Write(uint8_t data) { UART_Write(UART6, data); }
inline void UART7_Write(uint8_t data) { UART_Write(UART7, data); }
inline void UART8_Write(uint8_t data) { UART_Write(UART8, data); }

inline void UART1_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART1, data, size); }
inline void UART2_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART2, data, size); }
inline void UART3_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART3, data, size); }
inline void UART4_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART4, data, size); }
inline void UART5_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART5, data, size); }
inline void UART6_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART6, data, size); }
inline void UART7_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART7, data, size); }
inline void UART8_WriteBytes(uint8_t* data, uint8_t size) { UART_WriteBytes(UART8, data, size); }

inline uint8_t UART1_Read() { return UART_Read(UART1); }
inline uint8_t UART2_Read() { return UART_Read(UART2); }
inline uint8_t UART3_Read() { return UART_Read(UART3); }
inline uint8_t UART4_Read() { return UART_Read(UART4); }
inline uint8_t UART5_Read() { return UART_Read(UART5); }
inline uint8_t UART6_Read() { return UART_Read(UART6); }
inline uint8_t UART7_Read() { return UART_Read(UART7); }
inline uint8_t UART8_Read() { return UART_Read(UART8); }

inline void UART1_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART1, data, size); }
inline void UART2_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART2, data, size); }
inline void UART3_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART3, data, size); }
inline void UART4_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART4, data, size); }
inline void UART5_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART5, data, size); }
inline void UART6_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART6, data, size); }
inline void UART7_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART7, data, size); }
inline void UART8_ReadBytes(uint8_t* data, uint8_t* size) { UART_ReadBytes(UART8, data, size); }

inline bool UART1_IsDataAvailable() { return UART_IsDataAvailable(UART1); }
inline bool UART2_IsDataAvailable() { return UART_IsDataAvailable(UART2); }
inline bool UART3_IsDataAvailable() { return UART_IsDataAvailable(UART3); }
inline bool UART4_IsDataAvailable() { return UART_IsDataAvailable(UART4); }
inline bool UART5_IsDataAvailable() { return UART_IsDataAvailable(UART5); }
inline bool UART6_IsDataAvailable() { return UART_IsDataAvailable(UART6); }
inline bool UART7_IsDataAvailable() { return UART_IsDataAvailable(UART7); }
inline bool UART8_IsDataAvailable() { return UART_IsDataAvailable(UART8); }

inline uint8_t UART1_GetBytesAvailable() { return UART_GetBytesAvailable(UART1); }
inline uint8_t UART2_GetBytesAvailable() { return UART_GetBytesAvailable(UART2); }
inline uint8_t UART3_GetBytesAvailable() { return UART_GetBytesAvailable(UART3); }
inline uint8_t UART4_GetBytesAvailable() { return UART_GetBytesAvailable(UART4); }
inline uint8_t UART5_GetBytesAvailable() { return UART_GetBytesAvailable(UART5); }
inline uint8_t UART6_GetBytesAvailable() { return UART_GetBytesAvailable(UART6); }
inline uint8_t UART7_GetBytesAvailable() { return UART_GetBytesAvailable(UART7); }
inline uint8_t UART8_GetBytesAvailable() { return UART_GetBytesAvailable(UART8); }

void LPUART1_IRQHandler() { LPUART_IRQHandler(UART1); }
void LPUART2_IRQHandler() { LPUART_IRQHandler(UART2); }
void LPUART3_IRQHandler() { LPUART_IRQHandler(UART3); }
void LPUART4_IRQHandler() { LPUART_IRQHandler(UART4); }
void LPUART5_IRQHandler() { LPUART_IRQHandler(UART5); }
void LPUART6_IRQHandler() { LPUART_IRQHandler(UART6); }
void LPUART7_IRQHandler() { LPUART_IRQHandler(UART7); }
void LPUART8_IRQHandler() { LPUART_IRQHandler(UART8); }

static void LPUART_IRQHandler(UART_Peripheral_t uartNum)
{
    LPUART_Type* uart = peripheralToAddress[uartNum];

    for (uint8_t txCount = getTXFIFOCount(uart); txCount < UART_BUFFER_SIZE; txCount++)
    {
        if (txGetIndex[uartNum] == txPutIndex[uartNum])
        {
            uart->CTRL &= ~LPUART_CTRL_TIE_MASK;
            break;
        }
        uart->DATA |= txData[uartNum][txGetIndex[uartNum]];
        txGetIndex[uartNum]++;
    }

    for (uint8_t rxCount = getRXFIFOCount(uart); rxCount > 0; rxCount--)
    {
        rxData[uartNum][rxPutIndex[uartNum]] = uart->DATA & 0xFF;
        rxPutIndex[uartNum]++;
    }
}

static inline uint8_t getTXFIFOCount(LPUART_Type* uart)
{
    return ((uart->WATER & LPUART_WATER_TXCOUNT_MASK) >> LPUART_WATER_TXCOUNT_SHIFT);
}
static inline uint8_t getRXFIFOCount(LPUART_Type* uart)
{
    return ((uart->WATER & LPUART_WATER_RXCOUNT_MASK) >> LPUART_WATER_RXCOUNT_SHIFT);
}

static uint16_t getDivider(UART_Config_t* config)
{
    const uint32_t sourceClock = 80000000;
    uint16_t divider = sourceClock / config->overSamplingRatio / config->baudRate;

    while (divider == 0)
    {
        if (config->overSamplingRatio <= UART_MIN_OSR)
        {
            break;
        }
        config->overSamplingRatio--;
        divider = sourceClock / config->overSamplingRatio / config->baudRate;
    }
    while (divider > UART_MAX_DIVIDER)
    {
        if (config->overSamplingRatio >= UART_MAX_OSR)
        {
            break;
        }
        config->overSamplingRatio++;
        divider = sourceClock / config->overSamplingRatio / config->baudRate;
    }

    if (config->overSamplingRatio <= 7)
    {
        config->bothEdgeSampling = true;
    }

    return divider;
}

void putchar_(char c)
{
    UART5_Write(c);
}