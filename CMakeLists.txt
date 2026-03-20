cmake_minimum_required(VERSION 3.27.9)

# Fix for CI environment paths
if(DEFINED ENV{GEODE_SDK})
    file(TO_CMAKE_PATH "$ENV{GEODE_SDK}" GEODE_SDK_PATH)
    set(Geode_DIR "${GEODE_SDK_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK_PATH}")
endif()

# Find Geode - This is what pulls in Android/Mac/Win support
find_package(Geode REQUIRED CONFIG)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# Identify your source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

# Create the mod
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Links the SDK and prepares the .geode file
setup_geode_mod(${PROJECT_NAME})
