include(FetchContent)

FetchContent_Declare(
    CMSIS
    GIT_REPOSITORY https://github.com/Sociotorn/CMSIS_Core_CMake.git
    GIT_TAG develop
)

FetchContent_MakeAvailable(CMSIS)