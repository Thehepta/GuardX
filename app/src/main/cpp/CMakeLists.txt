# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("GuardX")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE")

add_subdirectory(customSshd)
add_subdirectory(davilkRuntime)
add_subdirectory(soInfo)

include_directories(davilkRuntime)

OPTION(LSPLT_BUILD_SHARED OFF)
add_subdirectory(lsplt)




add_library(GuardX SHARED
        artmethod_native_hook.cpp
        checkNative.cpp
        GuardX.cpp)


target_link_libraries(GuardX
        lsplt_static
        davilkRuntime
        soInfo
        log)