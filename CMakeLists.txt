cmake_minimum_required(VERSION 3.27.9)

# Fix for all platforms (Windows/Mac/Android) to find the SDK in CI
if(DEFINED ENV{GEODE_SDK})
    file(TO_CMAKE_PATH "$ENV{GEODE_SDK}" GEODE_SDK_PATH)
    set(Geode_DIR "${GEODE_SDK_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK_PATH}")
endif()

# The ONLY way to load Geode for all platforms in v3.0.0+
find_package(Geode REQUIRED CONFIG)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# Automatically find all source files in the src folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h src/*.c)

# Create the mod library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# This function is MAGIC: It handles Android NDK, macOS Architectures, 
# and Windows linking automatically for you.
setup_geode_mod(${PROJECT_NAME})
