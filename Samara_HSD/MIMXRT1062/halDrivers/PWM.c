#include "PWM.h"

static void setFrequency(PWM_Config_t *config);
static void writeA(PWM_Type *pwm, uint8_t submodule, int16_t value);
static void writeB(PWM_Type *pwm, uint8_t submodule, int16_t value);

static bool init = false;
void PWM_Init()
{
    if(init)
    {
        return;
    }

    CCM->CCGR4 = 0xFFFFFFFF;
    init = true;
}

void PWM_GetDefaultConfig(PWM_Config_t *config, PWM_Type *pwm, uint8_t submodule, PWM_OutChannel_t outChannel)
{
    config->pwm = pwm;
    config->subModule = submodule;
    config->outChannel = outChannel;
    config->indep = true;
    config->clockSource = PWM_CLKSRC_IPG;
    // 500 hz signal
    config->frequency = 500;
    config->dynamicFrequency = true;
}

void PWM_GetConfig(PWM_Config_t *config, PWM_Type *pwm, uint8_t submodule, PWM_OutChannel_t outChannel, bool indep, uint32_t frequency)
{
    config->pwm = pwm;
    config->subModule = submodule;
    config->outChannel = outChannel;
    config->indep = indep;
    config->clockSource = PWM_CLKSRC_IPG; // for some reason all clocks are at 150 MHZ need to investigate
    config->frequency = frequency;
    config->dynamicFrequency = true;
}

void PWM_GetCustomFrequencyConfig(PWM_Config_t *config, PWM_Type *pwm, uint8_t submodule, PWM_OutChannel_t outChannel, bool indep, uint16_t stepSize, PWM_Prescaler_t prescaler)
{
    config->pwm = pwm;
    config->subModule = submodule;
    config->outChannel = outChannel;
    config->indep = indep;
    config->clockSource = PWM_CLKSRC_IPG; // for some reason all clocks are at 150 MHZ need to investigate
    config->stepSize = stepSize;
    config->prescaler = prescaler;
    config->dynamicFrequency = false;
}

void PWM_SetConfig(PWM_Config_t *config)
{
    config->pwm->FCTRL = PWM_FCTRL_FLVL(15);
    config->pwm->FSTS = PWM_FSTS_FFLAG_MASK;
    config->pwm->FFILT = 0;
    config->pwm->MCTRL |= PWM_MCTRL_CLDOK(1 << config->subModule);

    setFrequency(config);

    config->pwm->SM[config->subModule].CTRL2 = PWM_CTRL2_INDEP(config->indep) | PWM_CTRL2_CLK_SEL(config->clockSource) | PWM_CTRL2_WAITEN_MASK; // PWM_CTRL2_FORCE_MASK;
    config->pwm->SM[config->subModule].DTCNT0 = 0;
    config->pwm->SM[config->subModule].OCTRL = 0;

    config->pwm->SM[config->subModule].VAL2 = 0;
    config->pwm->SM[config->subModule].VAL3 = 0;
    config->pwm->SM[config->subModule].VAL4 = 0;
    config->pwm->SM[config->subModule].VAL5 = 0;

    config->pwm->MCTRL |= PWM_MCTRL_LDOK(1 << config->subModule);
    config->pwm->OUTEN |= PWM_OUTEN_PWMAB(config->outChannel, config->subModule);
    config->pwm->MCTRL |= PWM_MCTRL_RUN(1 << config->subModule);
}

inline void PWM2_Write0A(int16_t value) { writeA(PWM2, 0, value); }
inline void PWM2_Write0B(int16_t value) { writeB(PWM2, 0, value); }
inline void PWM2_Write1A(int16_t value) { writeA(PWM2, 1, value); }
inline void PWM2_Write1B(int16_t value) { writeB(PWM2, 1, value); }
inline void PWM2_Write2A(int16_t value) { writeA(PWM2, 2, value); }
inline void PWM2_Write2B(int16_t value) { writeB(PWM2, 2, value); }
inline void PWM2_Write3A(int16_t value) { writeA(PWM2, 3, value); }
inline void PWM2_Write3B(int16_t value) { writeB(PWM2, 3, value); }

inline void PWM4_Write0A(int16_t value) { writeA(PWM4, 0, value); }
inline void PWM4_Write0B(int16_t value) { writeB(PWM4, 0, value); }
inline void PWM4_Write1A(int16_t value) { writeA(PWM4, 1, value); }
inline void PWM4_Write1B(int16_t value) { writeB(PWM4, 1, value); }
inline void PWM4_Write2A(int16_t value) { writeA(PWM4, 2, value); }
inline void PWM4_Write2B(int16_t value) { writeB(PWM4, 2, value); }
inline void PWM4_Write3A(int16_t value) { writeA(PWM4, 3, value); }
inline void PWM4_Write3B(int16_t value) { writeB(PWM4, 3, value); }

static inline void writeA(PWM_Type *pwm, uint8_t submodule, int16_t value)
{
    pwm->MCTRL |= PWM_MCTRL_CLDOK(1 << submodule);
    pwm->SM[submodule].VAL3 = value;
    pwm->MCTRL |= PWM_MCTRL_LDOK(1 << submodule);
}
static inline void writeB(PWM_Type *pwm, uint8_t submodule, int16_t value)
{
    pwm->MCTRL |= PWM_MCTRL_CLDOK(1 << submodule);
    pwm->SM[submodule].VAL5 = value;
    pwm->MCTRL |= PWM_MCTRL_LDOK(1 << submodule);
}

static void setFrequency(PWM_Config_t *config)
{
    const uint32_t clockFrequency = 132 MHZ;
    uint8_t prescalerReg = PWM_PRESCALER_1;
    uint8_t prescalerActual = 1;
    uint16_t stepSize = MINIMUM_STEPS; // minimum of 2000 steps

    if (config->dynamicFrequency)
    {
        while (prescalerReg < PWM_PRESCALER_128 && clockFrequency / MINIMUM_STEPS / (prescalerActual * 2) > config->frequency)
        {
            if (clockFrequency / stepSize / (prescalerActual * 2) > config->frequency)
            {
                prescalerReg++;
                prescalerActual *= 2;
            }
        }

        stepSize = (int32_t)((clockFrequency / prescalerActual / (double)config->frequency) + .5);
        if (stepSize > MAXINT16)
        {
            stepSize = MAXINT16;
        }
    }
    else
    {
        prescalerReg = config->prescaler;
        stepSize = config->stepSize;
    }

    config->pwm->SM[config->subModule].CTRL = PWM_CTRL_PRSC(prescalerReg) | PWM_CTRL_FULL_MASK;
    config->pwm->SM[config->subModule].INIT = 0;
    config->pwm->SM[config->subModule].VAL0 = stepSize / 2;
    config->pwm->SM[config->subModule].VAL1 = stepSize;
}
