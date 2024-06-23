#ifndef IOMUX_H
#define IOMUX_H

#include "MIMXRT1062.h"
#include "stdbool.h"
#include "pinInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        IOMUX_RESISTOR_100K_PULLDOWN,
        IOMUX_RESISTOR_47K_PULLUP,
        IOMUX_RESISTOR_100K_PULLUP,
        IOMUX_RESISTOR_22K_PULLDOWN,
        IOMUX_RESISTOR_NONE,
    } IOMUX_Resistor_t;

    typedef enum
    {
        IOMUX_SPEED_50MHZ,
        IOMUX_SPEED_100MHZ,
        IOMUX_SPEED_150MHZ, // default speed
        IOMUX_SPEED_200MHZ,
    } IOMUX_Speed_t;

    typedef enum
    {
        IOMUX_DRIVESTRENGTH_DISABLED,
        IOMUX_DRIVESTRENGTH_150,
        IOMUX_DRIVESTRENGTH_75,
        IOMUX_DRIVESTRENGTH_50,
        IOMUX_DRIVESTRENGTH_37,
        IOMUX_DRIVESTRENGTH_30,
        IOMUX_DRIVESTRENGTH_25, // default drive strength
        IOMUX_DRIVESTRENGTH_21,
    } IOMUX_DriveStrength_t;

    /**
     * @brief
     * Sets the alternative function and Software input on field for the given pin
     * @param pin_num teensy pin number
     * @param function alt mode function for pin, see datasheet
     * @param biDirectional enable Software input on field or not (generally usually false)
     */
    void IOMUX_SetMux(uint8_t pin_num, int8_t function, bool biDirectional);

    /**
     * @brief
     * Set the input pin on the daisy chain of the given peripheral
     * @param daisy_register daisy chain peripheral
     * @param daisy which pad to use, see datasheet
     */
    void IOMUX_SetInput(iomuxc_select_input_t daisy_register, int8_t daisy);

    /**
     * @brief
     * Sets all the pad values for a given pin
     * @param pin given teensy pin
     * @param hystersis hystersis enable or not
     * @param resistor pull up resistor setting(use enum)
     * @param openDrain open drain enable or not
     * @param speed pin speed(use enum)
     * @param driveStrength output drive stength(use enum)
     * @param slew slew enable or not
     */
    void IOMUX_SetPad(uint8_t pin, bool hystersis, IOMUX_Resistor_t resistor, bool openDrain, IOMUX_Speed_t speed, IOMUX_DriveStrength_t driveStrength, bool slew);

    /**
     * @brief
     * Sets the hystersis value for a given pin
     * @param pin_num given teensy pin
     * @param hysteris hysteris enable or not
     */
    void IOMUX_SetHystersis(uint8_t pin_num, bool hysteris);

    /**
     * @brief
     * Sets the pull up resistor for a given pin
     * @param pin_num given teensy pin
     * @param resistor pull up resistor setting(use enum)
     */
    void IOMUX_SetRes(uint8_t pin_num, IOMUX_Resistor_t resistor);

    /**
     * @brief
     * Sets the open drain for a given pin
     * @param pin_num given teensy pin
     * @param openDrain openDrain enable or not
     */
    void IOMUX_SetOpenDrain(uint8_t pin_num, bool openDrain);

    /**
     * @brief
     * Sets the speed for a given pin
     * @param pin_num given teensy pin
     * @param speed speed of pin(use enum)
     */
    void IOMUX_SetSpeed(uint8_t pin_num, IOMUX_Speed_t speed);

    /**
     * @brief
     * Sets the strength for a given pin
     * @param pin_num given teensy pin
     * @param drive_strength drive strength of pin(use enum)
     */
    void IOMUX_SetStrength(uint8_t pin_num, IOMUX_DriveStrength_t drive_strength);

    /**
     * @brief
     * Enables pin slew for a given pin
     * @param pin_num given teensy pin
     * @param slew_rate enable slew or not
     */
    void IOMUX_SetSlew(uint8_t pin_num, bool slew_rate);

#ifdef __cplusplus
}
#endif
#endif
