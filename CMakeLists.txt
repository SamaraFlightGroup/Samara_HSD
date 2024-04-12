add_library(SAMARA_HSD INTERFACE)

add_subdirectory(Samara_HAL)

include(fetchCMSIS.cmake)

add_subdirectory(Samara_HSD/MIMXRT1062)

target_link_libraries(SAMARA_HSD INTERFACE MIMXRT1062)