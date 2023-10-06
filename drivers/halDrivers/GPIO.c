#include "GPIO.h"
static bool init = false;
void GPIO_Init()
{
    if(init)
    {
        return;
    }
    
    CCM->CCGR0 |= CCM_CCGR0_CG15_MASK;                       // Enable GPIO 2 clock
    CCM->CCGR1 |= CCM_CCGR1_CG15_MASK | CCM_CCGR1_CG13_MASK; // Enable GPIO 5 and GPIO 1 clock
    CCM->CCGR2 |= CCM_CCGR2_CG13_MASK;                       // Enable GPIO 3 clock
    CCM->CCGR3 |= CCM_CCGR3_CG6_MASK;                        // Enable GPIO 4 clock

    IOMUXC_GPR->GPR26 = 0xFFFFFFFF;
    IOMUXC_GPR->GPR27 = 0xFFFFFFFF;
    IOMUXC_GPR->GPR28 = 0xFFFFFFFF;
    IOMUXC_GPR->GPR29 = 0xFFFFFFFF;

    GPIO_Mode(LED_PIN, OUTPUT);
    init = true;
}

void GPIO_Write(uint8_t pin_num, uint8_t value)
{
    if (value)
    {
        pinInfo[pin_num].gpio->DR_SET |= pinInfo[pin_num].gpioMask;
    }
    else
    {
        pinInfo[pin_num].gpio->DR_CLEAR |= pinInfo[pin_num].gpioMask;
    }
}

void GPIO_Tog(uint8_t pin_num)
{
    pinInfo[pin_num].gpio->DR_TOGGLE |= pinInfo[pin_num].gpioMask;
}

// 2 params pin, mode: input/output(0/1)
void GPIO_Mode(uint8_t pin_num, uint8_t mode)
{
    if (mode)
    {
        pinInfo[pin_num].gpio->GDIR |= pinInfo[pin_num].gpioMask;
    }
    else
    {
        pinInfo[pin_num].gpio->GDIR &= ~pinInfo[pin_num].gpioMask;
    }
}