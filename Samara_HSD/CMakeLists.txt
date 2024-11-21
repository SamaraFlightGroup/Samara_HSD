add_subdirectory(lib)
add_subdirectory(MIMXRT1062_HSD)

add_library(
    SAMARA_HSD STATIC

    "public/src/ssd_dma.c"

)

target_include_directories(SAMARA_HSD PUBLIC "public/include" PRIVATE "private/include")

target_link_libraries(SAMARA_HSD INTERFACE SAMARA_HAL MIMXRT1062_HSD)