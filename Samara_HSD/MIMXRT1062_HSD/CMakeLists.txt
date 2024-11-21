add_library(
    MIMXRT1062_HSD STATIC

    "public/src/GPIO.c"
    "public/src/IOMUX.c"
    "public/src/time.cpp"
    "public/src/PWM.c"
    "public/src/UART.c"
    "public/src/I2C.c"
    "public/src/ADC.c"

    "public/src/mimxrt1062_dma.c"
    "public/src/mimxrt1062_usart.c"
    "public/src/mimxrt1062_iomux.c"
)

set_property(GLOBAL PROPERTY MIMXRT1062_LINKER_FILE ${CMAKE_CURRENT_SOURCE_DIR}public/linker/MIMXRT1062.ld)

target_include_directories(MIMXRT1062_HSD PUBLIC public/include PRIVATE private/include)

target_link_libraries(MIMXRT1062_HSD SAMARA_HAL CMSIS)