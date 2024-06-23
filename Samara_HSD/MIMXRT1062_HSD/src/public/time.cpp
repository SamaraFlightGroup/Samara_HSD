#include "time.hpp"

static uint32_t overflow = 0;
//static uint8_t PITChannel = 0;
//static void (*PITfunctions[TIME_NUM_PIT_CHANNELS])();
//Task* PITObjects[TIME_NUM_PIT_CHANNELS];
//static uint32_t functionPeriods[TIME_NUM_PIT_CHANNELS];
//static uint32_t currPeriods[TIME_NUM_PIT_CHANNELS];
static bool init = false;
void Time_Init()
{
    if(init)
    {
        return;
    }
    // Enable timer clocks
    CCM->CCGR0 |= 0xF << CCM_CCGR0_CG12_SHIFT;                                  // enable GPT2 clock
    CCM->CCGR1 |= (0xF << CCM_CCGR1_CG10_SHIFT) | CCM_CCGR1_CG6_MASK;           // enable GPT1 clock, PIT clock
    CCM->CSCMR1 |= CCM_CSCMR1_PERCLK_CLK_SEL_MASK | CCM_CSCMR1_PERCLK_PODF(23); // set PIT and GPT clock source to 1MHZ

    // configure stopwatch timer
    GPT1->CR = GPT_CR_CLKSRC(0x1) | GPT_CR_STOPEN(1) | GPT_CR_DOZEEN(1) | GPT_CR_WAITEN(1) | GPT_CR_DBGEN(1); // GPT_CR_EN_24M(1) |  // Use PERCLCK source
    // GPT1->PR = GPT_PR_PRESCALER(23);
    GPT1->OCR[0] = 0xFFFFFFFF;

    NVIC_EnableIRQ(GPT1_IRQn);  // enable GPT interrupts
    GPT1->IR = GPT_IR_OF1IE(1); // enable Compare 1 interrupt
    GPT1->CR |= GPT_CR_EN(1);   // enable timer
    init = true;
}

/*void Time_SetPeriodic(void (*function)(), uint32_t period)
{
    const uint32_t clockFrequency = 1000000;

    PITfunctions[PITChannel] = function;
    functionPeriods[PITChannel] = period;
    currPeriods[PITChannel] = 0;

    PIT->MCR = 0;

    uint32_t loadValue = ((clockFrequency * period) / 1000) - 1; // removing -1 breaks code, need to look later
    PIT->CHANNEL[PITChannel].LDVAL = loadValue;

    PIT->CHANNEL[PITChannel].TCTRL = PIT_TCTRL_TIE_MASK;

    PIT->CHANNEL[PITChannel].TCTRL |= PIT_TCTRL_TEN_MASK;

    NVIC_EnableIRQ(PIT_IRQn);

    PITChannel++;
}*/

/*void Time_SetPeriodic(Task* p)
{
    //const uint32_t clockFrequency = 1000000;

    PITObjects[PITChannel] = p;
    functionPeriods[PITChannel] = p->getPeriod();
    currPeriods[PITChannel] = 0;

    PIT->MCR = 0;

    uint32_t loadValue = p->getPeriod() - 1; // removing -1 breaks code, need to look later
    PIT->CHANNEL[PITChannel].LDVAL = loadValue;

    PIT->CHANNEL[PITChannel].TCTRL = PIT_TCTRL_TIE_MASK;

    PIT->CHANNEL[PITChannel].TCTRL |= PIT_TCTRL_TEN_MASK;

    NVIC_EnableIRQ(PIT_IRQn);

    PITChannel++;
}*/

uint64_t Time_GetMicros()
{
    return GPT1->CNT + overflow * 0xFFFFFFFF;
}

uint64_t Time_GetMillis()
{
    return Time_GetMicros() / 1000;
}

uint64_t Time_GetDeltaMicros(uint64_t compareTime)
{
    uint64_t delta = Time_GetMicros() - compareTime;
    return delta;
}

uint64_t Time_GetDeltaMillis(uint64_t compareTime)
{
    uint64_t delta = Time_GetMillis() - compareTime;
    return delta;
}

void Time_Delay(uint32_t value)
{
    uint64_t begin = Time_GetMillis();
    while (Time_GetMillis() - begin < value)
        ;
}

void Time_DelayMicros(uint32_t value)
{
    uint64_t begin = Time_GetMicros();
    while (Time_GetMicros() - begin < value)
        ;
}

void GPT1_IRQHandler() asm("GPT1_IRQHandler"); //prevent C++ name mangling
void GPT1_IRQHandler()
{
    GPT1->SR = 0x3F;
    overflow++;
}

/*void PIT_IRQHandler() asm("PIT_IRQHandler"); //prevent C++ name mangling
void PIT_IRQHandler()
{
    for (uint8_t i = 0; i < TIME_NUM_PIT_CHANNELS; i++)
    {
        if ((PIT->CHANNEL[i].TFLG) & PIT_TFLG_TIF_MASK)
        {
            PITObjects[i]->periodicFunction();
        }
        PIT->CHANNEL[i].TFLG = PIT_TFLG_TIF_MASK;
    }
}*/