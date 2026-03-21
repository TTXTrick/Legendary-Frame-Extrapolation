cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# Manually define the SDK path based on the OS
if(WIN32)
    set(GEODE_SDK_PATH "$ENV{LOCALAPPDATA}/Geode/sdk")
else()
    set(GEODE_SDK_PATH "$ENV{HOME}/.geode/sdk")
endif()

# Force CMake to find Geode in that specific folder
find_package(Geode REQUIRED CONFIG HINTS "${GEODE_SDK_PATH}")

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Geode-specific setup
setup_geode_mod(${PROJECT_NAME})
