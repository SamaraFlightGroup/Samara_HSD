
add_library(MIMXRT1062 STATIC
src/GPIO.c
src/IOMUX.c
src/time.cpp
src/PWM.c
src/UART.c
src/I2C.c
src/ADC.c

src/teensy41PinInfo.c
)
target_include_directories(MIMXRT1062 PUBLIC include lib)
target_link_libraries(MIMXRT1062 CMSIS SAMARA_HAL)