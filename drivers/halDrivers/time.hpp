#ifndef TIME_HPP
#define TIME_HPP

#include "MIMXRT1062.h"

//#define TIME_NUM_PIT_CHANNELS 4

void Time_Init();
//void Time_SetPeriodic(void (*function)(), uint32_t period);
//void Time_SetPeriodic(Task* p);
uint64_t Time_GetMicros();
uint64_t Time_GetMillis();
uint64_t Time_GetDeltaMicros(uint64_t compareTime);
uint64_t Time_GetDeltaMillis(uint64_t compareTime);
void Time_Delay(uint32_t value);
void Time_DelayMicros(uint32_t value);
#endif