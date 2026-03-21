cmake_minimum_required(VERSION 3.27.9)

# Standard Geode SDK discovery for CI
if(DEFINED ENV{GEODE_SDK})
    file(TO_CMAKE_PATH "$ENV{GEODE_SDK}" GEODE_SDK_PATH)
    set(Geode_DIR "${GEODE_SDK_PATH}")
endif()

find_package(Geode REQUIRED CONFIG)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# Automatically find all your source files in the src folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

# Define the mod library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# This handles the cross-compilation for iOS (arm64) and Android automatically
setup_geode_mod(${PROJECT_NAME})
