#include "GPIO.h"

static const uint32_t mask[42] =
    {
        3,  // 0
        2,  // 1
        4,  // 2
        5,  // 3
        6,  // 4
        8,  // 5
        10, // 6
        17, // 7
        16, // 8
        11, // 9
        0,  // 10
        2,  // 11
        1,  // 12
        3,  // 13
        18, // 14
        19, // 15
        23, // 16
        22, // 17
        17, // 18
        16, // 19
        26, // 20
        27, // 21
        24, // 22
        25, // 23
        12, // 24
        13, // 25
        30, // 26
        31, // 27
        18, // 28
        31, // 29
        23, // 30
        22, // 31
        12, // 32
        7,  // 33
        29, // 34
        28, // 35
        18, // 36
        19, // 37
        28, // 38
        29, // 39
        20, // 40
        21, // 41
};
static GPIO_Type *pin_gpiotype[42] =
    {
        GPIO6, // 0
        GPIO6, // 1
        GPIO9, // 2
        GPIO9, // 3
        GPIO9, // 4
        GPIO9, // 5
        GPIO7, // 6
        GPIO7, // 7
        GPIO7, // 8
        GPIO7, // 9
        GPIO7, // 10
        GPIO7, // 11
        GPIO7, // 12
        GPIO7, // 13
        GPIO6, // 14
        GPIO6, // 15
        GPIO6, // 16
        GPIO6, // 17
        GPIO6, // 18
        GPIO6, // 19
        GPIO6, // 20
        GPIO6, // 21
        GPIO6, // 22
        GPIO6, // 23
        GPIO6, // 24
        GPIO6, // 25
        GPIO6, // 26
        GPIO6, // 27
        GPIO8, // 28
        GPIO9, // 29
        GPIO8, // 30
        GPIO8, // 31
        GPIO7, // 32
        GPIO9, // 33
        GPIO7, // 34
        GPIO7, // 35
        GPIO7, // 36
        GPIO7, // 37
        GPIO6, // 38
        GPIO6, // 39
        GPIO6, // 40
        GPIO6, // 41
};

void GPIO_Init()
{
    CCM->CCGR0 |= CCM_CCGR0_CG15_MASK;                       // Enable GPIO 2 clock
    CCM->CCGR1 |= CCM_CCGR1_CG15_MASK | CCM_CCGR1_CG13_MASK; // Enable GPIO 5 and GPIO 1 clock
    CCM->CCGR2 |= CCM_CCGR2_CG13_MASK;                       // Enable GPIO 3 clock
    CCM->CCGR3 |= CCM_CCGR3_CG6_MASK;                        // Enable GPIO 4 clock

    IOMUXC_GPR->GPR26 = 0xFFFFFFFF;
    IOMUXC_GPR->GPR27 = 0xFFFFFFFF;
    IOMUXC_GPR->GPR28 = 0xFFFFFFFF;
    IOMUXC_GPR->GPR29 = 0xFFFFFFFF;

    GPIO_Mode(13, OUTPUT);
}

void GPIO_Write(uint8_t pin_num, uint8_t value)
{
    if (value)
    {
        pin_gpiotype[pin_num]->DR_SET |= (1 << mask[pin_num]);
    }
    else
    {
        pin_gpiotype[pin_num]->DR_CLEAR |= (1 << mask[pin_num]);
    }
}

void GPIO_Tog(uint8_t pin_num)
{
    pin_gpiotype[pin_num]->DR_TOGGLE |= (1 << mask[pin_num]);
}

// 2 params pin, mode: input/output(0/1)
void GPIO_Mode(uint8_t pin_num, uint8_t mode)
{
    if (mode)
    {
        pin_gpiotype[pin_num]->GDIR |= (1 << mask[pin_num]);
    }
    else
    {
        pin_gpiotype[pin_num]->GDIR &= ~(1 << mask[pin_num]);
    }
}

// GP Timer Experiement
/*
  GPT_CNT_COUNT(0xFFFFFFF);
  GPT_CR_EN(1);
*/