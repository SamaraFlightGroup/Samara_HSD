#include "IOMUX.h"

// 2 params: pin, function
void IOMUX_MuxSet(uint8_t pin_num, uint8_t function, bool biDirectional)
{
    IOMUXC->SW_MUX_CTL_PAD[pinInfo[pin_num].iomuxMuxCtl] = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(function) | IOMUXC_SW_MUX_CTL_PAD_SION(biDirectional);
}

// 2 params; input register number (0-153), change pad
void IOMUX_Input(iomuxc_select_input_t daisy_register, uint8_t daisy)
{
    IOMUXC->SELECT_INPUT[daisy_register] = IOMUXC_SELECT_INPUT_DAISY(daisy);
}

void IOMUX_SetPad(uint8_t pin, bool hystersis, IOMUX_Resistor_t resistor, bool openDrain, IOMUX_Speed_t speed, IOMUX_DriveStrength_t driveStrength, bool slew)
{
    IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin].iomuxPadCtl] = IOMUXC_SW_PAD_CTL_PAD_HYS(hystersis) | IOMUXC_SW_PAD_CTL_PAD_PKE(1) |
        IOMUXC_SW_PAD_CTL_PAD_PUE(resistor >> 2) | IOMUXC_SW_PAD_CTL_PAD_PUS(resistor & 0x3) |
        IOMUXC_SW_PAD_CTL_PAD_ODE(openDrain) | IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) |
        IOMUXC_SW_PAD_CTL_PAD_DSE(driveStrength) | IOMUXC_SW_PAD_CTL_PAD_SRE(slew);
}

void IOMUX_Hystersis(uint8_t pin_num, bool hysteris)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] & ~(IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_HYS(hysteris);
    IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] = temp;
}

// 4 params: pin, resistor 1-4, disable/enable, keep/pull
void IOMUX_Res(uint8_t pin_num, IOMUX_Resistor_t resistor)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] & ~(IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_PKE(1) | IOMUXC_SW_PAD_CTL_PAD_PUE(resistor >> 2) | IOMUXC_SW_PAD_CTL_PAD_PUS(resistor & 0x3);
    IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] = temp;
}

void IOMUX_OpenDrain(uint8_t pin_num, bool openDrain)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] & ~(IOMUXC_SW_PAD_CTL_PAD_ODE_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_ODE(openDrain);
    IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] = temp;
}

// 2 params: pin, speed low/medium/fast/max
void IOMUX_Speed(uint8_t pin_num, IOMUX_Speed_t speed)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] & ~(IOMUXC_SW_PAD_CTL_PAD_SPEED_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_SPEED(speed);
    IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] = temp;
}

// 2 params: pin, drive strength: 0-7
void IOMUX_Strength(uint8_t pin_num, IOMUX_DriveStrength_t drive_strength)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] & ~(IOMUXC_SW_PAD_CTL_PAD_DSE_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_DSE(drive_strength);
    IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] = temp;
}

// 2 params: pin, slew: low/fast
void IOMUX_Slew(uint8_t pin_num, bool slew_rate)
{
    uint32_t temp = IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] & ~(IOMUXC_SW_PAD_CTL_PAD_SRE_MASK);
    temp |= IOMUXC_SW_PAD_CTL_PAD_SRE(slew_rate);
    IOMUXC->SW_PAD_CTL_PAD[pinInfo[pin_num].iomuxPadCtl] = temp;
}