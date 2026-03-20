cmake_minimum_required(VERSION 3.27.9)

# THE CRITICAL FIX: Manually points CMake to the SDK location on CI runners.
# This solves the "Could not find a package configuration file" error.
if(DEFINED ENV{GEODE_SDK})
    file(TO_CMAKE_PATH "$ENV{GEODE_SDK}" GEODE_SDK_PATH)
    set(Geode_DIR "${GEODE_SDK_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK_PATH}")
else()
    # Fallback for Linux/macOS hidden directories
    set(Geode_DIR "$ENV{HOME}/.geode/sdk")
    list(APPEND CMAKE_PREFIX_PATH "${Geode_DIR}")
endif()

# Find the Geode package (Works for Win, Mac, Android, and iOS)
find_package(Geode REQUIRED CONFIG)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# Automatically finds all your code in the src folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

# Define the mod library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# This handles the heavy lifting for iOS (arm64) and Android (NDK) automatically.
setup_geode_mod(${PROJECT_NAME})
