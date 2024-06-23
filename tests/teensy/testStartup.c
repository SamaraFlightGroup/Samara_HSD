// #include "GPIO.h"
#include "MIMXRT1062.h"

int main()
{
    // GPIO_Init();
    // GPIO_Write(LED_PIN,HIGH);
    GPIO2->GDIR   |= 1 << 3;
    GPIO2->DR_SET |= 1 << 3;

    return 0;
}