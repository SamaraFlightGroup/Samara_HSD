#ifndef GPIO_H
#define GPIO_H

#include "MIMXRT1062.h"
#include "pinInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

  void GPIO_Init();
  void GPIO_Write(uint8_t pin_num, uint8_t value);
  void GPIO_Tog(uint8_t pin_num);
  void GPIO_Mode(uint8_t pin_num, uint8_t mode);

#ifdef __cplusplus
}
#endif
#endif