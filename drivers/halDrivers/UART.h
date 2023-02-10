#ifndef UART_H
#define UART_H


#include "MIMXRT1062.h"
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define UART_NUM_PERIPHERALS 8 + 1 // dummy UART0
#define UART_MAX_DIVIDER 8191
#define UART_MAX_OSR 32
#define UART_MIN_OSR 4
#define UART_BUFFER_SIZE 4

    typedef enum
    {
        THERE_IS_NO_UART0_FOR_SOME_DUMB_REASON,
        UART1,
        UART2,
        UART3,
        UART4,
        UART5,
        UART6,
        UART7,
        UART8,
    } UART_Peripheral_t;

    typedef enum
    {
        UART_NOPARITY,
        UART_EVENPARITY,
        UART_ODDPARITY = 3,
    } UART_Parity_t;

    /*typedef enum
    {
        UART_FIFOSIZE_1,
        UART_FIFOSIZE_4,
        UART_FIFOSIZE_8,
        UART_FIFOSIZE_16,
        UART_FIFOSIZE_32,
        UART_FIFOSIZE_64,
        UART_FIFOSIZE_128,
        UART_FIFOSIZE_256,
    } UART_FIFOSize_t;*/

    typedef struct
    {
        LPUART_Type* uart;
        UART_Peripheral_t uartNum : 4;

        bool tenBitMode : 1;
        uint8_t overSamplingRatio : 5;
        bool bothEdgeSampling : 1;
        bool MSBFirst : 1;
        bool txInvert : 1;
        bool rxInvert : 1;
        UART_Parity_t parity : 2;
        bool twoStopBits : 1;

        uint32_t baudRate;
    } UART_Config_t;

    void UART_Init();
    void printf_Init();
    void UART_GetDefaultConfig(UART_Config_t* config, UART_Peripheral_t uartNum, uint32_t baudRate);
    void UART_GetConfig(UART_Config_t* config, UART_Peripheral_t uartNum, uint32_t baudRate, bool tenBitMode, uint8_t overSamplingRatio, bool bothEdgeSampling, bool MSBFirst, bool txInvert, bool rxInvert, UART_Parity_t parity, bool twoStopBits);
    void UART_SetConfig(UART_Config_t* config);

    void UART1_Write(uint8_t data);
    void UART2_Write(uint8_t data);
    void UART3_Write(uint8_t data);
    void UART4_Write(uint8_t data);
    void UART5_Write(uint8_t data);
    void UART6_Write(uint8_t data);
    void UART7_Write(uint8_t data);
    void UART8_Write(uint8_t data);

    void UART1_WriteBytes(uint8_t* data, uint8_t size);
    void UART2_WriteBytes(uint8_t* data, uint8_t size);
    void UART3_WriteBytes(uint8_t* data, uint8_t size);
    void UART4_WriteBytes(uint8_t* data, uint8_t size);
    void UART5_WriteBytes(uint8_t* data, uint8_t size);
    void UART6_WriteBytes(uint8_t* data, uint8_t size);
    void UART7_WriteBytes(uint8_t* data, uint8_t size);
    void UART8_WriteBytes(uint8_t* data, uint8_t size);

    uint8_t UART1_Read();
    uint8_t UART2_Read();
    uint8_t UART3_Read();
    uint8_t UART4_Read();
    uint8_t UART5_Read();
    uint8_t UART6_Read();
    uint8_t UART7_Read();
    uint8_t UART8_Read();

    void UART1_ReadBytes(uint8_t* data, uint8_t* size);
    void UART2_ReadBytes(uint8_t* data, uint8_t* size);
    void UART3_ReadBytes(uint8_t* data, uint8_t* size);
    void UART4_ReadBytes(uint8_t* data, uint8_t* size);
    void UART5_ReadBytes(uint8_t* data, uint8_t* size);
    void UART6_ReadBytes(uint8_t* data, uint8_t* size);
    void UART7_ReadBytes(uint8_t* data, uint8_t* size);
    void UART8_ReadBytes(uint8_t* data, uint8_t* size);

    bool UART1_IsDataAvailable();
    bool UART2_IsDataAvailable();
    bool UART3_IsDataAvailable();
    bool UART4_IsDataAvailable();
    bool UART5_IsDataAvailable();
    bool UART6_IsDataAvailable();
    bool UART7_IsDataAvailable();
    bool UART8_IsDataAvailable();

    uint8_t UART1_GetBytesAvailable();
    uint8_t UART2_GetBytesAvailable();
    uint8_t UART3_GetBytesAvailable();
    uint8_t UART4_GetBytesAvailable();
    uint8_t UART5_GetBytesAvailable();
    uint8_t UART6_GetBytesAvailable();
    uint8_t UART7_GetBytesAvailable();
    uint8_t UART8_GetBytesAvailable();

#ifdef __cplusplus
}
#endif
#endif