#ifndef ADC_H
#define ADC_H

#include "MIMXRT1062.h"
#include <stdbool.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C"
{

#define ADC_VREFHI 3.3
#define ADC_VREFLO 0

    typedef enum
    {
        NO_ADC0,
        ADC_1,
        ADC_2
    } ADC_num_t;

    void ADC_Init();
    void ADC_SetConfig();
    uint16_t ADC_Read();

    //uint16_t ADC2_Read();
    //uint16_t ADC1_Read();
}
#endif
#endif
