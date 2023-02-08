#include "IOMUX.h"

static const uint32_t pin_to_reg[42] =
    {
        45,  //	GPIO_AD_B0_03
        44,  //	GPIO_AD_B0_02
        4,   //	GPIO_EMC_04
        5,   //	GPIO_EMC_05
        6,   //	GPIO_EMC_06
        8,   //	GPIO_EMC_08
        84,  //	GPIO_B0_10
        91,  //	GPIO_B1_01
        90,  //	GPIO_B1_00
        85,  //	GPIO_B0_11
        74,  //	GPIO_B0_00
        76,  //	GPIO_B0_02
        75,  //	GPIO_B0_01
        77,  //	GPIO_B0_03
        60,  //	GPIO_AD_B1_02
        61,  //	GPIO_AD_B1_03
        65,  //	GPIO_AD_B1_07
        64,  //	GPIO_AD_B1_06
        59,  //	GPIO_AD_B1_01
        58,  //	GPIO_AD_B1_00
        68,  //	GPIO_AD_B1_10
        69,  //	GPIO_AD_B1_11
        66,  //	GPIO_AD_B1_08
        67,  //	GPIO_AD_B1_09
        55,  //	GPIO_AD_B0_12
        56,  //	GPIO_AD_B0_13
        72,  //	GPIO_AD_B1_14
        73,  //	GPIO_AD_B1_15
        32,  //	GPIO_EMC_32
        31,  //	GPIO_EMC_31
        37,  //	GPIO_EMC_37
        36,  //	GPIO_EMC_36
        86,  //	GPIO_B0_12
        7,   //	GPIO_EMC_07
        103, //	GPIO_B1_13
        102, //	GPIO_B1_12
        92,  //	GPIO_B1_02
        93,  //	GPIO_B1_03
        70,  //	GPIO_AD_B1_12
        71,  //	GPIO_AD_B1_13
        62,  //	GPIO_AD_B1_04
        63,  //	GPIO_AD_B1_05
};

// 2 params: pin, function
void IOMUX_MuxSet(uint8_t pin_num, uint8_t function, bool biDirectional)
{
    IOMUXC->SW_MUX_CTL_PAD[pin_to_reg[pin_num]] = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(function) | IOMUXC_SW_MUX_CTL_PAD_SION(biDirectional);
}

// 2 params; input register number (0-153), change pad
void IOMUX_Input(iomuxc_select_input_t daisy_register, uint8_t daisy)
{
    IOMUXC->SELECT_INPUT[daisy_register] = IOMUXC_SELECT_INPUT_DAISY(daisy);
}

void IOMUX_SetPad(uint8_t pin, bool hystersis, IOMUX_Resistor_t resistor, bool openDrain, IOMUX_Speed_t speed, IOMUX_DriveStrength_t driveStrength, bool slew)
{
    IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin]] = IOMUXC_SW_PAD_CTL_PAD_HYS(hystersis) | IOMUXC_SW_PAD_CTL_PAD_PKE(1) |
                                              IOMUXC_SW_PAD_CTL_PAD_PUE(resistor >> 2) | IOMUXC_SW_PAD_CTL_PAD_PUS(resistor & 0x3) |
                                              IOMUXC_SW_PAD_CTL_PAD_ODE(openDrain) | IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) |
                                              IOMUXC_SW_PAD_CTL_PAD_DSE(driveStrength) | IOMUXC_SW_PAD_CTL_PAD_SRE(slew);
}

void IOMUX_Hystersis(uint8_t pin_num, bool hysteris)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] & ~(IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_HYS(hysteris);
    IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] = temp;
}

// 4 params: pin, resistor 1-4, disable/enable, keep/pull
void IOMUX_Res(uint8_t pin_num, IOMUX_Resistor_t resistor)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] & ~(IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_PKE(1) | IOMUXC_SW_PAD_CTL_PAD_PUE(resistor >> 2) | IOMUXC_SW_PAD_CTL_PAD_PUS(resistor & 0x3);
    IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] = temp;
}

void IOMUX_OpenDrain(uint8_t pin_num, bool openDrain)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] & ~(IOMUXC_SW_PAD_CTL_PAD_ODE_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_ODE(openDrain);
    IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] = temp;
}

// 2 params: pin, speed low/medium/fast/max
void IOMUX_Speed(uint8_t pin_num, IOMUX_Speed_t speed)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] & ~(IOMUXC_SW_PAD_CTL_PAD_SPEED_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_SPEED(speed);
    IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] = temp;
}

// 2 params: pin, drive strength: 0-7
void IOMUX_Strength(uint8_t pin_num, IOMUX_DriveStrength_t drive_strength)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] & ~(IOMUXC_SW_PAD_CTL_PAD_DSE_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_DSE(drive_strength);
    IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] = temp;
}

// 2 params: pin, slew: low/fast
void IOMUX_Slew(uint8_t pin_num, uint8_t slew_rate)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] & ~(IOMUXC_SW_PAD_CTL_PAD_SRE_MASK);
    if (slew_rate)
    {
        temp |= IOMUXC_SW_PAD_CTL_PAD_SRE(1);
    }
    IOMUXC->SW_PAD_CTL_PAD[pin_to_reg[pin_num]] = temp;
}