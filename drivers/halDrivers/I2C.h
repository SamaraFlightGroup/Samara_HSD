#ifndef I2C_H
#define I2C_H

#include "MIMXRT1062.h"
#include <stdbool.h>
#include <stddef.h>
#include "GPIO.h"
#include "printf.h"
#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // Main Here
#define I2C_NUM_PERIPHERALS 4 + 1
#define I2C_MAX_PRESCALER 7 // 7 is a divider of 128

#define I2C_SCL_LOW_PERCENTAGE 66 // 75 percent low for SCL, must be 50 or greater
#define I2C_SCL_HIGH_PERCENTAGE (100 - I2C_SCL_LOW_PERCENTAGE)

#define I2C_MAX_SCL_LOW 63                                                                      // max value of SCL low
#define I2C_MAX_SCL_HIGH ((I2C_MAX_SCL_LOW * I2C_SCL_HIGH_PERCENTAGE) / I2C_SCL_LOW_PERCENTAGE) // max value SCL high with ratio in mind
#define I2C_MAX_SCL_PERIOD I2C_MAX_SCL_LOW + I2C_MAX_SCL_HIGH + 4                               // Max scl_period value(add high and low) and Add 4 for additional latency

#define I2C_BUFFER_SIZE 4

    typedef enum
    {
        THERE_IS_NO_I2C0_FOR_SOME_DUMB_REASON,
        I2C1,
        I2C2,
        I2C3,
        I2C4,
    } I2C_Peripheral_t;

    typedef struct
    {
        LPI2C_Type* i2c;
        I2C_Peripheral_t i2cNum : 3;
        uint32_t baudrate;
        bool autostop : 1;
    } I2C_Config_t;

    typedef enum
    {
        I2C_COMMAND_TRANSMIT = 0b000,
        I2C_COMMAND_RECIEVE = 0b001,
        I2C_COMMAND_STOP = 0b010,
        I2C_COMMAND_RECIEVE_DISCARD = 0b011,
        I2C_COMMAND_START_ADDRESS = 0b100,
        I2C_COMMAND_START_ADDRESS_NACK = 0b101,
        I2C_COMMAND_START_ADDRESS_HS = 0b110,
        I2C_COMMAND_START_ADDRESS_NACK_HS = 0b111,
    } I2C_Command_t;

    typedef enum
    {
        I2C_DIRECTION_WRITE,
        I2C_DIRECTION_READ,
        I2C_DIRECTION_NONE
    } I2C_Direction_t;

    typedef struct
    {
        I2C_Command_t cmd;
        uint8_t data;
    } I2C_CommandPacket_t;

    void I2C_Init();

    void I2C_GetDefaultConfig(I2C_Config_t* config, I2C_Peripheral_t i2cNum, uint32_t baudRate);

    void I2C_SetConfig(I2C_Config_t* config);

    void I2C1_Start(uint8_t addr, I2C_Direction_t dir);
    void I2C2_Start(uint8_t addr, I2C_Direction_t dir);
    void I2C3_Start(uint8_t addr, I2C_Direction_t dir);
    void I2C4_Start(uint8_t addr, I2C_Direction_t dir);

    void I2C1_Write(uint8_t data);
    void I2C2_Write(uint8_t data);
    void I2C3_Write(uint8_t data);
    void I2C4_Write(uint8_t data);

    void I2C1_Receive(uint8_t numBytes);
    void I2C2_Receive(uint8_t numBytes);
    void I2C3_Receive(uint8_t numBytes);
    void I2C4_Receive(uint8_t numBytes);

    void I2C1_Stop();
    void I2C2_Stop();
    void I2C3_Stop();
    void I2C4_Stop();

    uint8_t I2C1_Read();
    uint8_t I2C2_Read();
    uint8_t I2C3_Read();
    uint8_t I2C4_Read();

    void I2C1_ReadBytes(uint8_t* data, uint8_t* size);
    void I2C2_ReadBytes(uint8_t* data, uint8_t* size);
    void I2C3_ReadBytes(uint8_t* data, uint8_t* size);
    void I2C4_ReadBytes(uint8_t* data, uint8_t* size);

    bool I2C1_IsDataAvailable();
    bool I2C2_IsDataAvailable();
    bool I2C3_IsDataAvailable();
    bool I2C4_IsDataAvailable();

    uint8_t I2C1_GetBytesAvailable();
    uint8_t I2C2_GetBytesAvailable();
    uint8_t I2C3_GetBytesAvailable();
    uint8_t I2C4_GetBytesAvailable();

    void I2C_Start(I2C_Peripheral_t i2cNum, uint8_t addr, I2C_Direction_t dir);
    void I2C_Write(I2C_Peripheral_t i2cNum, uint8_t data);
    void I2C_Receive(I2C_Peripheral_t i2cNum, uint8_t numBytes);
    void I2C_Stop(I2C_Peripheral_t i2cNum);
    uint8_t I2C_Read(I2C_Peripheral_t i2cNum);
    void I2C_ReadBytes(I2C_Peripheral_t i2cNum, uint8_t* data, uint8_t* size);
    bool I2C_IsDataAvailable(I2C_Peripheral_t i2cNum);
    uint8_t I2C_GetBytesAvailable(I2C_Peripheral_t i2cNum);

    // End
#ifdef __cplusplus
}
#endif
#endif