add_library(STARTUP STATIC
src/startup_mimxrt1062.cpp
src/system_MIMXRT1062.c
)
target_include_directories(STARTUP PUBLIC include)
target_link_libraries(STARTUP MIMXRT1062)