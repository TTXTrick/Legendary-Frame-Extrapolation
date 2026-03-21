cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 1. Determine the path where the CLI installs the SDK
if(WIN32)
    set(GEODE_SDK_ROOT "$ENV{LOCALAPPDATA}/Geode/sdk")
else()
    set(GEODE_SDK_ROOT "$ENV{HOME}/.geode/sdk")
endif()

# 2. If find_package fails, manually include the Geode CMake logic
find_package(Geode CONFIG HINTS "${GEODE_SDK_ROOT}")

if(NOT Geode_FOUND)
    message(STATUS "Standard find_package failed, attempting manual include...")
    include("${GEODE_SDK_ROOT}/loader/CMakeLists.txt" OPTIONAL RESULT_VARIABLE GEODE_LOADER_INCLUDED)
    if(NOT GEODE_LOADER_INCLUDED)
        message(FATAL_ERROR "Could not find Geode SDK at ${GEODE_SDK_ROOT}. Please ensure the SDK is installed.")
    endif()
endif()

# 3. Source discovery
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 4. Standard Geode setup
setup_geode_mod(${PROJECT_NAME})
