add_library(HALDRIVERS STATIC
GPIO.c
IOMUX.c
time.cpp
PWM.c
UART.c
I2C.c
ADC.c
)
target_include_directories(HALDRIVERS PUBLIC .)
target_link_libraries(HALDRIVERS DEVICE PININFO PRINTF PORKEROS)