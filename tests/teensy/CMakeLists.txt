cmake_minimum_required(VERSION 3.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_TOOLCHAIN_FILE "toolchain.cmake")

project(testSamaraHSD)
enable_testing()

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_VERBOSE_MAKEFILE true)

enable_language(C CXX ASM)
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED on)
set(CXX_EXTENSIONS off)
set(C_STANDARD 17)
set(C_STANDARD_REQUIRED on)
set(C_EXTENSIONS off)

set(TEST_SOURCES
    testGPIO.c
)
set(LINKER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/linker/MIMXRT1062_EVK_Debug.ld)

add_compile_options(
    # optimization settings
    -Os #optimize for size
    -fdata-sections # Reduce size with --gc-sections

    -g0
    # cpu settings
    -mcpu=cortex-m7 #m7 cpu
    -mfpu=fpv5-sp-d16 #floating point type
    -mfloat-abi=hard #hardware float
    -mthumb #thum instructions
    # debugging settings

    # Dialect options
    -ffreestanding #No stdlib
    -fno-builtin #no builtin functions
    -fno-exceptions # no exceptions

    #developer options
    -fstack-usage # output stack usage
    #warnings
    -Wall
    -Wextra
    -Wpedantic
    -Werror #Make warnings errors
    -Wfloat-equal # warn float equal
    -Wswitch-default #warn no default
    -Wstack-usage=10000 #warn very large stack
)

add_compile_definitions(

        CPU_MIMXRT1062DVJ6A
        CPU_MIMXRT1062DVJ6A_cm7

        XIP_EXTERNAL_FLASH=1
        XIP_BOOT_HEADER_ENABLE=1

        __MCUXPRESSO
        __USE_CMSIS
        DEBUG

        TEENSY41
        _XOPEN_SOURCE
)

add_link_options(
        #linker file
        -T${LINKER_FILE}

        #ARM cpu options
        -mcpu=cortex-m7
        -mthumb
        -mfpu=fpv5-sp-d16
        -mfloat-abi=hard

        #link options
        -nostdlib

        # linker options
        -Wl,--gc-sections
        -Wl,-print-memory-usage
)

add_subdirectory(../.. ../../build/SAMARA_HSD)
add_subdirectory(boot)
add_subdirectory(startup)

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    set(TEST_EXECUTABLE "${TEST_NAME}.elf")

    set(TEST_SOURCE
    ${TEST_SOURCE}
    boot/src/evkmimxrt1060_flexspi_nor_config.c
    boot/src/fsl_flexspi_nor_boot.c
    )

    add_executable(${TEST_EXECUTABLE} ${TEST_SOURCE})

    target_link_libraries(${TEST_EXECUTABLE} SAMARA_HSD STARTUP BOOT)
    target_link_directories(${TEST_EXECUTABLE} PRIVATE linker)

    # Optional: Print executable size as part of the post build process
    add_custom_command(TARGET ${TEST_EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${TEST_EXECUTABLE})

    # Optional: Create hex, bin and S-Record files after the build
    add_custom_command(TARGET ${TEST_EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 ${TEST_EXECUTABLE} ${TEST_NAME}.s19
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${TEST_EXECUTABLE} ${TEST_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary ${TEST_EXECUTABLE} ${TEST_NAME}.bin)

endforeach(TEST_SOURCE TEST_SOURCES)