#ifndef TEENSY41_PIN_INFO_H
#define TEENSY41_PIN_INFO_H

#include "MIMXRT1062.h"
#include "I2C.h"
#include "UART.h"

#define NUM_OF_PINS 41
#define LED_PIN 13

#define IOMUXC_MUX_MODE(x) IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(x)
typedef struct
{
    GPIO_Type* gpio;
    uint32_t gpioMask;
    uint8_t gpioMuxMode;
    iomuxc_sw_pad_ctl_pad_t iomuxPadCtl;
    iomuxc_sw_mux_ctl_pad_t iomuxMuxCtl;
}PinInfo_General_t;

typedef enum
{
    PININFO_I2CPINTYPE_NONE,
    PININFO_I2CPINTYPE_SDA,
    PININFO_I2CPINTYPE_SCL,
    PININFO_I2CPINTYPE_HREQ,
    PININFO_I2CPINTYPE_SDAS,
    PININFO_I2CPINTYPE_SCLS,
}PinInfo_I2CPinType_t;

typedef struct
{
    PinInfo_I2CPinType_t pinType;
    I2C_Peripheral_t i2c;
    uint8_t muxMode;
    iomuxc_select_input_t selectInputIndex;
    uint8_t selectInput;
}PinInfo_I2C_t;

typedef enum
{
    PININFO_UARTPINTYPE_NONE,
    PININFO_UARTPINTYPE_TX,
    PININFO_UARTPINTYPE_RX,
    PININFO_UARTPINTYPE_CTS,
    PININFO_UARTPINTYPE_RTS,
}PinInfo_UARTPinType_t;

typedef struct
{
    PinInfo_UARTPinType_t pinType;
    UART_Peripheral_t uart;
    int8_t muxMode;
    iomuxc_select_input_t selectInputIndex;
    int8_t selectInput;
}PinInfo_UART_t;


extern const PinInfo_General_t pinInfo[];
extern const PinInfo_I2C_t pinInfoI2C[];
extern const PinInfo_UART_t pinInfoUART[];
#endif