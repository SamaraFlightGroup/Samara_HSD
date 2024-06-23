#include "teensy41PinInfo.h"

const PinInfo_General_t pinInfo[] =
{
    {GPIO6, 1 << 3,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03,}, //0 GPIO_AD_B0_03
    {GPIO6, 1 << 2,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_02, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02,}, // 1 GPIO_AD_B0_02
    {GPIO9, 1 << 4,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_04,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04,  }, // 2 GPIO_EMC_04
    {GPIO9, 1 << 5,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_05,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05,  }, // 3 GPIO_EMC_05
    {GPIO9, 1 << 6,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_06,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06,  }, // 4 GPIO_EMC_06
    {GPIO9, 1 << 8,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_08,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08,  }, // 5 GPIO_EMC_08
    {GPIO7, 1 << 10, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_10,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10,   }, // 6 GPIO_B0_10
    {GPIO7, 1 << 17, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_01,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01,   }, // 7 GPIO_B1_01
    {GPIO7, 1 << 16, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_00,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00,   }, // 8 GPIO_B1_00
    {GPIO7, 1 << 11, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_11,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11,   }, // 9 GPIO_B0_11
    {GPIO7, 1 << 0,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00,   }, // 10 GPIO_B0_00
    {GPIO7, 1 << 2,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02,   }, // 11 GPIO_B0_02
    {GPIO7, 1 << 1,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01,   }, // 12 GPIO_B0_01
    {GPIO7, 1 << 3,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03,   }, // 13 GPIO_B0_03
    {GPIO6, 1 << 18, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02,}, // 14 GPIO_AD_B1_02
    {GPIO6, 1 << 19, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03,}, // 15 GPIO_AD_B1_03
    {GPIO6, 1 << 23, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_07, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07,}, // 16 GPIO_AD_B1_07
    {GPIO6, 1 << 22, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_06, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06,}, // 17 GPIO_AD_B1_06
    {GPIO6, 1 << 17, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01,}, // 18 GPIO_AD_B1_01
    {GPIO6, 1 << 16, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00,}, // 19 GPIO_AD_B1_00
    {GPIO6, 1 << 26, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_10, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10,}, // 20 GPIO_AD_B1_10
    {GPIO6, 1 << 27, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_11, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11,}, // 21 GPIO_AD_B1_11
    {GPIO6, 1 << 24, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_08, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08,}, // 22 GPIO_AD_B1_08
    {GPIO6, 1 << 25, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_09, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09,}, // 23 GPIO_AD_B1_09
    {GPIO6, 1 << 12, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_12, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12,}, // 24 GPIO_AD_B0_12
    {GPIO6, 1 << 13, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_13, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13,}, // 25 GPIO_AD_B0_13
    {GPIO6, 1 << 30, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_14, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_14,}, // 26 GPIO_AD_B1_14
    {GPIO6, 1 << 31, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_15, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_15,}, // 27 GPIO_AD_B1_15
    {GPIO8, 1 << 18, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_32,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32,  }, // 28 GPIO_EMC_32
    {GPIO9, 1 << 31, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_31,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31,  }, // 29 GPIO_EMC_31
    {GPIO8, 1 << 23, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_37,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_37,  }, // 30 GPIO_EMC_37
    {GPIO8, 1 << 22, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_36,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_36,  }, // 31 GPIO_EMC_36
    {GPIO7, 1 << 12, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B0_12,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B0_12,   }, // 32 GPIO_B0_12
    {GPIO9, 1 << 7,  5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_07,   kIOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_07,  }, // 33 GPIO_EMC_07
    {GPIO7, 1 << 29, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_13,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_13,   }, // 34 GPIO_B1_13
    {GPIO7, 1 << 28, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_12,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_12,   }, // 35 GPIO_B1_12
    {GPIO7, 1 << 18, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_02,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_02,   }, // 36 GPIO_B1_02
    {GPIO7, 1 << 19, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_B1_03,    kIOMUXC_SW_MUX_CTL_PAD_GPIO_B1_03,   }, // 37 GPIO_B1_03
    {GPIO6, 1 << 28, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_12, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_12,}, // 38 GPIO_AD_B1_12
    {GPIO6, 1 << 29, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_13, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_13,}, // 39 GPIO_AD_B1_13
    {GPIO6, 1 << 20, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_04, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_04,}, // 40 GPIO_AD_B1_04
    {GPIO6, 1 << 21, 5, kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_05, kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_05,}, // 41 GPIO_AD_B1_05 
};

const PinInfo_I2C_t pinInfoI2C[] =
{
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 0 GPIO_AD_B0_03
    {PININFO_I2CPINTYPE_HREQ, I2C1,   IOMUXC_MUX_MODE(6),  -1,                              -1                          }, // 1 GPIO_AD_B0_02
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 2 GPIO_EMC_04
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 3 GPIO_EMC_05
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 4 GPIO_EMC_06
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 5 GPIO_EMC_08
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 6 GPIO_B0_10
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 7 GPIO_B1_01
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 8 GPIO_B1_00
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 9 GPIO_B0_11
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 10 GPIO_B0_00
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 11 GPIO_B0_02
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 12 GPIO_B0_01
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 13 GPIO_B0_03
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 14 GPIO_AD_B1_02
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 15 GPIO_AD_B1_03
    {PININFO_I2CPINTYPE_SCL,  I2C3,   IOMUXC_MUX_MODE(1),  kIOMUXC_LPI2C3_SCL_SELECT_INPUT, IOMUXC_SELECT_INPUT_DAISY(2)}, // 16 GPIO_AD_B1_07
    {PININFO_I2CPINTYPE_SDA,  I2C3,   IOMUXC_MUX_MODE(1),  kIOMUXC_LPI2C3_SDA_SELECT_INPUT, IOMUXC_SELECT_INPUT_DAISY(2)}, // 17 GPIO_AD_B1_06
    {PININFO_I2CPINTYPE_SDA,  I2C1,   IOMUXC_MUX_MODE(3),  kIOMUXC_LPI2C1_SDA_SELECT_INPUT, IOMUXC_SELECT_INPUT_DAISY(1)}, // 18 GPIO_AD_B1_01
    {PININFO_I2CPINTYPE_SCL,  I2C1,   IOMUXC_MUX_MODE(3),  kIOMUXC_LPI2C1_SCL_SELECT_INPUT, IOMUXC_SELECT_INPUT_DAISY(1)}, // 19 GPIO_AD_B1_00
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 20 GPIO_AD_B1_10
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 21 GPIO_AD_B1_11
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 22 GPIO_AD_B1_08
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 23 GPIO_AD_B1_09
    {PININFO_I2CPINTYPE_SCL,  I2C4,   IOMUXC_MUX_MODE(0),  kIOMUXC_LPI2C4_SCL_SELECT_INPUT, IOMUXC_SELECT_INPUT_DAISY(1)}, // 24 GPIO_AD_B0_12
    {PININFO_I2CPINTYPE_SDA,  I2C4,   IOMUXC_MUX_MODE(0),  kIOMUXC_LPI2C4_SDA_SELECT_INPUT, IOMUXC_SELECT_INPUT_DAISY(1)}, // 25 GPIO_AD_B0_13
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 26 GPIO_AD_B1_14
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 27 GPIO_AD_B1_15
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 28 GPIO_EMC_32
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 29 GPIO_EMC_31
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 30 GPIO_EMC_37
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 31 GPIO_EMC_36
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 32 GPIO_B0_12
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 33 GPIO_EMC_07
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 34 GPIO_B1_13
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 35 GPIO_B1_12
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 36 GPIO_B1_02
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 37 GPIO_B1_03
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 38 GPIO_AD_B1_12
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 39 GPIO_AD_B1_13
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 40 GPIO_AD_B1_04
    {PININFO_I2CPINTYPE_NONE, NO_I2C, -1,                  -1,                              -1                          }, // 41 GPIO_AD_B1_05 
};

const PinInfo_UART_t pinInfoUART[] =
{
    {PININFO_UARTPINTYPE_RX,   UART6,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART6_RX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 0 GPIO_AD_B0_03
    {PININFO_UARTPINTYPE_TX,   UART6,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART6_TX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 1 GPIO_AD_B0_02
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 2 GPIO_EMC_04 
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 3 GPIO_EMC_05
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 4 GPIO_EMC_06
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 5 GPIO_EMC_08
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 6 GPIO_B0_10
    {PININFO_UARTPINTYPE_RX,   UART4,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART4_RX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(2)}, // 7 GPIO_B1_01
    {PININFO_UARTPINTYPE_TX,   UART4,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART4_TX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(2)}, // 8 GPIO_B1_00
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 9 GPIO_B0_11
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 10 GPIO_B0_00  
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 11 GPIO_B0_02  
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 12 GPIO_B0_01
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 13 GPIO_B0_03
    {PININFO_UARTPINTYPE_TX,   UART2,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART2_TX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 14 GPIO_AD_B1_02
    {PININFO_UARTPINTYPE_RX,   UART2,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART2_RX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 15 GPIO_AD_B1_03
    {PININFO_UARTPINTYPE_RX,   UART3,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART3_RX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 16 GPIO_AD_B1_07
    {PININFO_UARTPINTYPE_TX,   UART3,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART3_TX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 17 GPIO_AD_B1_06
    {PININFO_UARTPINTYPE_RTS,  UART2,    IOMUXC_MUX_MODE(2), -1,                                 -1                          }, // 18 GPIO_AD_B1_01
    {PININFO_UARTPINTYPE_CTS,  UART2,    IOMUXC_MUX_MODE(2), -1,                                 -1                          }, // 19 GPIO_AD_B1_00
    {PININFO_UARTPINTYPE_TX,   UART8,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART8_TX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 20 GPIO_AD_B1_10
    {PININFO_UARTPINTYPE_RX,   UART8,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART8_RX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 21 GPIO_AD_B1_11
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 22 GPIO_AD_B1_08
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 23 GPIO_AD_B1_09
    {PININFO_UARTPINTYPE_TX  , UART1   , IOMUXC_MUX_MODE(2), -1,                                 -1                          }, // 24 GPIO_AD_B0_12
    {PININFO_UARTPINTYPE_RX  , UART1   , IOMUXC_MUX_MODE(2), -1,                                 -1                          }, // 25 GPIO_AD_B0_13
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 26 GPIO_AD_B1_14
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 27 GPIO_AD_B1_15
    {PININFO_UARTPINTYPE_RX,   UART7,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART7_RX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 28 GPIO_EMC_32
    {PININFO_UARTPINTYPE_TX,   UART7,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART7_TX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 29 GPIO_EMC_31
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 30 GPIO_EMC_37
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 31 GPIO_EMC_36
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 32 GPIO_B0_12
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 33 GPIO_EMC_07
    {PININFO_UARTPINTYPE_RX,   UART5,    IOMUXC_MUX_MODE(1), kIOMUXC_LPUART5_RX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 34 GPIO_B1_13
    {PININFO_UARTPINTYPE_TX,   UART5,    IOMUXC_MUX_MODE(1), kIOMUXC_LPUART5_TX_SELECT_INPUT,    IOMUXC_SELECT_INPUT_DAISY(1)}, // 35 GPIO_B1_12
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 36 GPIO_B1_02 
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 37 GPIO_B1_03
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 38 GPIO_AD_B1_12
    {PININFO_UARTPINTYPE_NONE, NO_UART0, -1,                 -1,                                 -1                          }, // 39 GPIO_AD_B1_13
    {PININFO_UARTPINTYPE_CTS,  UART3,    IOMUXC_MUX_MODE(2), kIOMUXC_LPUART3_CTS_B_SELECT_INPUT, IOMUXC_SELECT_INPUT_DAISY(1)}, // 40 GPIO_AD_B1_04
    {PININFO_UARTPINTYPE_RTS,  UART3,    IOMUXC_MUX_MODE(2), -1,                                 -1                          }, // 41 GPIO_AD_B1_05
};