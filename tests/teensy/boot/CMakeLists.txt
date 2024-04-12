add_library(BOOT STATIC
src/evkmimxrt1060_flexspi_nor_config.c
src/fsl_flexspi_nor_boot.c
)
target_include_directories(BOOT PUBLIC include)
target_link_libraries(BOOT MIMXRT1062)