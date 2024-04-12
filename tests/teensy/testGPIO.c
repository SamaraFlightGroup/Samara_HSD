#include "GPIO.h"

int main()
{
    GPIO_Init();
    GPIO_Write(LED_PIN,HIGH);

    return 0;
}