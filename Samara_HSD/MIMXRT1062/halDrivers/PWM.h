#ifndef PWM_H
#define PWM_H

#include "MIMXRT1062.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MHZ *1000000
#define KHZ *1000

#define STEP_SIZE 1000

#define PWM_OUTEN_PWMAB(outchannel, submodule) (PWM_OUTEN_PWMA_EN((outchannel & 1) << submodule) | PWM_OUTEN_PWMB_EN(((outchannel >> 1) & 1) << submodule))
#define MINIMUM_STEPS 2000
#define MAXUINT16 65535
#define MAXINT16 32767

    typedef enum
    {
        PWM_CLKSRC_IPG,
        PWM_CLKSRC_EXTERNAL,
        PWM_CLKSRC_AUXCLOCK,
    } PWM_ClkSrc_t;

    typedef enum
    {
        PWM_OUTCHANNEL_A = 1,
        PWM_OUTCHANNEL_B,
        PWM_OUTCHANNEL_BOTH,
    } PWM_OutChannel_t;

    typedef enum
    {
        PWM_PRESCALER_1,
        PWM_PRESCALER_2,
        PWM_PRESCALER_4,
        PWM_PRESCALER_8,
        PWM_PRESCALER_16,
        PWM_PRESCALER_32,
        PWM_PRESCALER_64,
        PWM_PRESCALER_128,
    } PWM_Prescaler_t;

    typedef struct
    {
        PWM_Type *pwm;
        PWM_ClkSrc_t clockSource : 2;
        uint8_t subModule : 2;
        PWM_OutChannel_t outChannel : 2;
        bool indep : 1;

        bool dynamicFrequency : 1; // if true then uses frequency register, otherwise uses custom step size and prescaler
        uint16_t stepSize;
        PWM_Prescaler_t prescaler : 3;
        uint32_t frequency;
    } PWM_Config_t;

    void PWM_Init();
    void PWM_GetDefaultConfig(PWM_Config_t *config, PWM_Type *pwm, uint8_t submodule, PWM_OutChannel_t outChannel);
    void PWM_GetConfig(PWM_Config_t *config, PWM_Type *pwm, uint8_t submodule, PWM_OutChannel_t outChannel, bool indep, uint32_t frequency);
    void PWM_GetCustomFrequencyConfig(PWM_Config_t *config, PWM_Type *pwm, uint8_t submodule, PWM_OutChannel_t outChannel, bool indep, uint16_t stepSize, PWM_Prescaler_t prescaler);

    void PWM_SetConfig(PWM_Config_t *config);

    void PWM2_Write0A(int16_t value);
    void PWM2_Write0B(int16_t value);
    void PWM2_Write1A(int16_t value);
    void PWM2_Write1B(int16_t value);
    void PWM2_Write2A(int16_t value);
    void PWM2_Write2B(int16_t value);
    void PWM2_Write3A(int16_t value);
    void PWM2_Write3B(int16_t value);

    void PWM4_Write0A(int16_t value);
    void PWM4_Write0B(int16_t value);
    void PWM4_Write1A(int16_t value);
    void PWM4_Write1B(int16_t value);
    void PWM4_Write2A(int16_t value);
    void PWM4_Write2B(int16_t value);
    void PWM4_Write3A(int16_t value);
    void PWM4_Write3B(int16_t value);

#ifdef __cplusplus
}
#endif
#endif
