add_subdirectory(MIMXRT1062_HSD)
# add_subdirectory(LinuxSim)

add_library(SAMARA_HSD INTERFACE)

target_link_libraries(SAMARA_HSD INTERFACE MIMXRT1062_HSD)