#include "I2C.h"

static LPI2C_Type* peripheralToAddress[I2C_NUM_PERIPHERALS] = { NULL, LPI2C1, LPI2C2, LPI2C3, LPI2C4 };
static const IRQn_Type peripheralToIRQ[I2C_NUM_PERIPHERALS] = LPI2C_IRQS;

static I2C_Direction_t currentDirection[I2C_NUM_PERIPHERALS] = { I2C_DIRECTION_NONE, I2C_DIRECTION_NONE, I2C_DIRECTION_NONE, I2C_DIRECTION_NONE, I2C_DIRECTION_NONE };

static uint8_t rxData[I2C_NUM_PERIPHERALS][255];
static uint8_t rxPutIndex[I2C_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0 };
static uint8_t rxGetIndex[I2C_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0 };

static I2C_CommandPacket_t cmdBuffer[I2C_NUM_PERIPHERALS][255];
static uint8_t cmdPutIndex[I2C_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0 };
static uint8_t cmdGetIndex[I2C_NUM_PERIPHERALS] = { 0, 0, 0, 0, 0 };

static void I2C_Command(I2C_Peripheral_t i2cNum, I2C_Command_t cmd, uint8_t data);
static void LPI2C_IRQHandler(I2C_Peripheral_t i2cNum);
static uint8_t getTXFIFOCount(LPI2C_Type* i2c);
static uint8_t getRXFIFOCount(LPI2C_Type* i2c);
static void setBaudRate(I2C_Config_t* config);
// static bool arbitrationLost(I2C_Peripheral_t i2cNum);

static bool init = false;
void I2C_Init()
{
    if(init)
    {
        return;
    }
    // pin 19 is SCL ICM
    // pin 18 is SDA ICM
    CCM->CCGR2 |= CCM_CCGR2_CG3_MASK | CCM_CCGR2_CG4_MASK | CCM_CCGR2_CG5_MASK; // enable LPI2C(1,2,3) clocks
    CCM->CCGR6 |= CCM_CCGR6_CG12_MASK;                                          // enable LPI2C4 clocks
    CCM->CSCDR2 &= ~(CCM_CSCDR2_LPI2C_CLK_PODF_MASK | CCM_CSCDR2_LPI2C_CLK_SEL_MASK);
    init = true;
}

void I2C_GetDefaultConfig(I2C_Config_t* config, I2C_Peripheral_t i2cNum, uint32_t baudRate)
{
    config->i2c = peripheralToAddress[i2cNum];
    config->i2cNum = i2cNum;
    config->baudrate = baudRate;
    config->autostop = false;
}

void I2C_SetConfig(I2C_Config_t* config)
{
    // Reset I2C registers
    config->i2c->MCR = LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK | LPI2C_MCR_RST_MASK;
    config->i2c->MCR &= ~(LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK | LPI2C_MCR_RST_MASK);

    setBaudRate(config);

    // config->i2c->MCFGR0 = 0;
    config->i2c->MCFGR1 |= LPI2C_MCFGR1_AUTOSTOP(config->autostop);

    // config->i2c->MCFGR3 = 0;

    config->i2c->MFCR = LPI2C_MFCR_TXWATER(2) | LPI2C_MFCR_RXWATER(0);

    config->i2c->MIER = LPI2C_MIER_RDIE_MASK; // enable interrupts

    NVIC_EnableIRQ(peripheralToIRQ[config->i2cNum]);

    config->i2c->MCR = LPI2C_MCR_MEN_MASK;
}

inline void I2C1_Start(uint8_t addr, I2C_Direction_t dir) { I2C_Start(I2C1, addr, dir); }
inline void I2C2_Start(uint8_t addr, I2C_Direction_t dir) { I2C_Start(I2C2, addr, dir); }
inline void I2C3_Start(uint8_t addr, I2C_Direction_t dir) { I2C_Start(I2C3, addr, dir); }
inline void I2C4_Start(uint8_t addr, I2C_Direction_t dir) { I2C_Start(I2C4, addr, dir); }

inline void I2C1_Write(uint8_t data) { I2C_Write(I2C1, data); }
inline void I2C2_Write(uint8_t data) { I2C_Write(I2C2, data); }
inline void I2C3_Write(uint8_t data) { I2C_Write(I2C3, data); }
inline void I2C4_Write(uint8_t data) { I2C_Write(I2C4, data); }

inline void I2C1_Receive(uint8_t numBytes) { I2C_Receive(I2C1, numBytes); }
inline void I2C2_Receive(uint8_t numBytes) { I2C_Receive(I2C2, numBytes); }
inline void I2C3_Receive(uint8_t numBytes) { I2C_Receive(I2C3, numBytes); }
inline void I2C4_Receive(uint8_t numBytes) { I2C_Receive(I2C4, numBytes); }

inline void I2C1_Stop() { I2C_Stop(I2C1); }
inline void I2C2_Stop() { I2C_Stop(I2C2); }
inline void I2C3_Stop() { I2C_Stop(I2C3); }
inline void I2C4_Stop() { I2C_Stop(I2C4); }

inline uint8_t I2C1_Read() { return I2C_Read(I2C1); }
inline uint8_t I2C2_Read() { return I2C_Read(I2C2); }
inline uint8_t I2C3_Read() { return I2C_Read(I2C3); }
inline uint8_t I2C4_Read() { return I2C_Read(I2C4); }

inline void I2C1_ReadBytes(uint8_t* data, uint8_t* size) { I2C_ReadBytes(I2C1, data, size); }
inline void I2C2_ReadBytes(uint8_t* data, uint8_t* size) { I2C_ReadBytes(I2C2, data, size); }
inline void I2C3_ReadBytes(uint8_t* data, uint8_t* size) { I2C_ReadBytes(I2C3, data, size); }
inline void I2C4_ReadBytes(uint8_t* data, uint8_t* size) { I2C_ReadBytes(I2C4, data, size); }

inline bool I2C1_IsDataAvailable() { return I2C_IsDataAvailable(I2C1); }
inline bool I2C2_IsDataAvailable() { return I2C_IsDataAvailable(I2C2); }
inline bool I2C3_IsDataAvailable() { return I2C_IsDataAvailable(I2C3); }
inline bool I2C4_IsDataAvailable() { return I2C_IsDataAvailable(I2C4); }

inline uint8_t I2C1_GetBytesAvailable() { return I2C_GetBytesAvailable(I2C1); }
inline uint8_t I2C2_GetBytesAvailable() { return I2C_GetBytesAvailable(I2C2); }
inline uint8_t I2C3_GetBytesAvailable() { return I2C_GetBytesAvailable(I2C3); }
inline uint8_t I2C4_GetBytesAvailable() { return I2C_GetBytesAvailable(I2C4); }

void LPI2C1_IRQHandler() { LPI2C_IRQHandler(I2C1); }
void LPI2C2_IRQHandler() { LPI2C_IRQHandler(I2C2); }
void LPI2C3_IRQHandler() { LPI2C_IRQHandler(I2C3); }
void LPI2C4_IRQHandler() { LPI2C_IRQHandler(I2C4); }

void I2C_Start(I2C_Peripheral_t i2cNum, uint8_t addr, I2C_Direction_t dir)
{
    I2C_Command(i2cNum, I2C_COMMAND_START_ADDRESS, (addr << 1) | dir);
    currentDirection[i2cNum] = dir;
}

void I2C_Write(I2C_Peripheral_t i2cNum, uint8_t data)
{
    if (currentDirection[i2cNum] != I2C_DIRECTION_WRITE)
        return;
    I2C_Command(i2cNum, I2C_COMMAND_TRANSMIT, data);
}

void I2C_Receive(I2C_Peripheral_t i2cNum, uint8_t numBytes)
{
    if (currentDirection[i2cNum] != I2C_DIRECTION_READ)
        return;
    for (uint8_t i = 0; i < numBytes; i++)
    {
        I2C_Command(i2cNum, I2C_COMMAND_RECIEVE, 0);
    }
}

void I2C_Stop(I2C_Peripheral_t i2cNum)
{
    I2C_Command(i2cNum, I2C_COMMAND_STOP, 0);
    currentDirection[i2cNum] = I2C_DIRECTION_NONE;
}

uint8_t I2C_Read(I2C_Peripheral_t i2cNum)
{
    uint8_t data = 0xEE;

    if (I2C_IsDataAvailable(i2cNum))
    {
        data = rxData[i2cNum][rxGetIndex[i2cNum]];
        rxGetIndex[i2cNum]++;
    }
    return data;
}

void I2C_ReadBytes(I2C_Peripheral_t i2cNum, uint8_t* data, uint8_t* size)
{
    if (I2C_GetBytesAvailable(i2cNum) < *size)
    {
        *size = I2C_GetBytesAvailable(i2cNum);
    }

    for (uint8_t i = 0; i < *size; i++)
    {
        data[i] = rxData[i2cNum][rxGetIndex[i2cNum]];
        rxGetIndex[i2cNum]++;
    }
}

bool I2C_IsDataAvailable(I2C_Peripheral_t i2cNum)
{
    return rxGetIndex[i2cNum] != rxPutIndex[i2cNum];
}

uint8_t I2C_GetBytesAvailable(I2C_Peripheral_t i2cNum)
{
    if (rxGetIndex[i2cNum] < rxPutIndex[i2cNum])
    {
        return rxPutIndex[i2cNum] - rxGetIndex[i2cNum];
    }
    else if (rxGetIndex[i2cNum] > rxPutIndex[i2cNum])
    {
        return 255 - rxGetIndex[i2cNum] + rxPutIndex[i2cNum] + 1;
    }
    else
    {
        return 0;
    }
}

static void I2C_Command(I2C_Peripheral_t i2cNum, I2C_Command_t cmd, uint8_t data)
{
    LPI2C_Type* i2c = peripheralToAddress[i2cNum];
    I2C_CommandPacket_t packet;
    packet.cmd = cmd;
    packet.data = data;

    cmdBuffer[i2cNum][cmdPutIndex[i2cNum]] = packet;
    cmdPutIndex[i2cNum]++;
    i2c->MIER |= LPI2C_MIER_TDIE_MASK;
}

static void LPI2C_IRQHandler(I2C_Peripheral_t i2cNum)
{
    LPI2C_Type* i2c = peripheralToAddress[i2cNum];

    for (uint8_t txCount = getTXFIFOCount(i2c); txCount < I2C_BUFFER_SIZE; txCount++)
    {
        if (cmdGetIndex[i2cNum] == cmdPutIndex[i2cNum])
        {
            i2c->MIER &= ~LPI2C_MIER_TDIE_MASK;
            break;
        }
        i2c->MTDR = LPI2C_MTDR_CMD(cmdBuffer[i2cNum][cmdGetIndex[i2cNum]].cmd) | LPI2C_MTDR_DATA(cmdBuffer[i2cNum][cmdGetIndex[i2cNum]].data);
        cmdGetIndex[i2cNum]++;
    }

    for (uint8_t rxCount = getRXFIFOCount(i2c); rxCount > 0; rxCount--)
    {
        rxData[i2cNum][rxPutIndex[i2cNum]] = i2c->MRDR;
        rxPutIndex[i2cNum]++;
    }
}

static inline uint8_t getTXFIFOCount(LPI2C_Type* i2c)
{
    return ((i2c->MFSR & LPI2C_MFSR_TXCOUNT_MASK) >> LPI2C_MFSR_TXCOUNT_SHIFT);
}

static inline uint8_t getRXFIFOCount(LPI2C_Type* i2c)
{
    return ((i2c->MFSR & LPI2C_MFSR_RXCOUNT_MASK) >> LPI2C_MFSR_RXCOUNT_SHIFT);
}

static void setBaudRate(I2C_Config_t* config)
{
    const uint32_t sourceClock = 60000000;

    uint8_t prescaler = 0;
    uint32_t currentFrequency = sourceClock;
    while (currentFrequency / I2C_MAX_SCL_PERIOD > config->baudrate)
    {
        prescaler++;
        currentFrequency /= 2;
        if (prescaler == I2C_MAX_PRESCALER)
        {
            break;
        }
    }

    uint16_t SCLPeriodValue = (currentFrequency / config->baudrate) - 5;
    uint8_t SCLLowValue = (uint8_t)((SCLPeriodValue * I2C_SCL_LOW_PERCENTAGE) / 100 + 3);   // 50
    uint8_t SCLHighValue = (uint8_t)((SCLPeriodValue * I2C_SCL_HIGH_PERCENTAGE) / 100 + 1); // 21

    // config->i2c->MCCR0 = LPI2C_MCCR0_DATAVD(0x08) | LPI2C_MCCR0_SETHOLD(0x11) | LPI2C_MCCR0_CLKHI(0x11) | LPI2C_MCCR0_CLKLO(0x28); // LPI2C_MCCR0_DATAVD(1) | LPI2C_MCCR0_SETHOLD(SCLHighValue + 1) | LPI2C_MCCR0_CLKHI(SCLHighValue) | LPI2C_MCCR0_CLKLO(SCLLowValue);
    // config->i2c->MCFGR1 = LPI2C_MCFGR1_PRESCALE(1);
    // config->i2c->MCFGR2 = LPI2C_MCFGR2_FILTSCL(0x2) | LPI2C_MCFGR2_FILTSDA(0x2) | LPI2C_MCFGR2_BUSIDLE((0x11 + 0x28 + 1) * 2);
    //  config->i2c->MCFGR3 = LPI2C_MCFGR3_PINLOW(704);

    // config->i2c->MCCR0 = LPI2C_MCCR0_DATAVD(0x08) | LPI2C_MCCR0_SETHOLD(0x11) | LPI2C_MCCR0_CLKHI(0x1f) | LPI2C_MCCR0_CLKLO(0x28); // LPI2C_MCCR0_DATAVD(1) | LPI2C_MCCR0_SETHOLD(SCLHighValue + 1) | LPI2C_MCCR0_CLKHI(SCLHighValue) | LPI2C_MCCR0_CLKLO(SCLLowValue);
    // config->i2c->MCFGR1 = LPI2C_MCFGR1_PRESCALE(1);
    // config->i2c->MCFGR2 = LPI2C_MCFGR2_FILTSCL(0x02) | LPI2C_MCFGR2_FILTSDA(0x02) | LPI2C_MCFGR2_BUSIDLE((0x1f + 0x28 + 1) * 2);
    // config->i2c->MCFGR3 = 0;

    config->i2c->MCCR0 = LPI2C_MCCR0_DATAVD(SCLLowValue / 2) | LPI2C_MCCR0_SETHOLD(SCLHighValue) | LPI2C_MCCR0_CLKHI(SCLHighValue) | LPI2C_MCCR0_CLKLO(SCLLowValue);
    config->i2c->MCFGR1 = (prescaler);
    config->i2c->MCFGR2 = LPI2C_MCFGR2_FILTSCL(0x1) | LPI2C_MCFGR2_FILTSDA(0x1) | LPI2C_MCFGR2_BUSIDLE((SCLHighValue + SCLLowValue + 2) * 2);
    config->i2c->MCCR1 = config->i2c->MCCR0;
}