cmake_minimum_required(VERSION 3.27.9)

# 1. First, try the standard environment variable (Works on Windows)
if(DEFINED ENV{GEODE_SDK})
    file(TO_CMAKE_PATH "$ENV{GEODE_SDK}" GEODE_SDK_PATH)
    set(Geode_DIR "${GEODE_SDK_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK_PATH}")
endif()

# 2. THE FIX: If the environment variable fails (Linux/Mac runners), force the default path.
if(NOT Geode_DIR)
    # The Geode CLI always installs here by default on Unix systems
    set(Geode_DIR "$ENV{HOME}/.geode/sdk")
    list(APPEND CMAKE_PREFIX_PATH "${Geode_DIR}")
endif()

# 3. Find Geode using the paths we just defined
find_package(Geode REQUIRED CONFIG)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

setup_geode_mod(${PROJECT_NAME})
