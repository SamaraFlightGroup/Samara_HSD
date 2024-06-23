add_subdirectory(lib/MIMXRT1062_Lib_CMake)

add_library(
    MIMXRT1062_HSD STATIC

    "src/public/GPIO.c"
    "src/public/IOMUX.c"
    "src/public/time.cpp"
    "src/public/PWM.c"
    "src/public/UART.c"
    "src/public/I2C.c"
    "src/public/ADC.c"
)

target_include_directories(MIMXRT1062_HSD PUBLIC include/public lib PRIVATE include/private)

target_link_libraries(MIMXRT1062_HSD SAMARA_HAL MIMXRT1062_LIB)