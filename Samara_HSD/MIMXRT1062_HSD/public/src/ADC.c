#include "ADC.h"

void ADC_Init()
{
    CCM->CCGR1 |= CCM_CCGR1_CG8_MASK | CCM_CCGR1_CG4_MASK; // Enable ADC 1 and ADC 2 clock
}
void ADC_SetConfig()
{
    while(ADC1->GS & ADC_GS_CALF_MASK == 1)
        ;

    while(ADC2->GS & ADC_GS_CALF_MASK == 1)
        ;
    const uint32_t ipgClock = 132000000;
    ADC1->CFG = ADC_CFG_ADICLK(0) | ADC_CFG_MODE(2) | ADC_CFG_ADSTS(3) | ADC_CFG_OVWREN(1) | ADC_CFG_AVGS(0);
    ADC1->GC = ADC_GC_AVGE(1) | ADC_GC_ADCO(1);
    ADC1->HC[0] = ADC_HC_ADCH(0);

}

uint16_t ADC_Read()
{
    uint16_t readValue = ADC1->R[0] & ADC_R_CDATA_MASK;
}