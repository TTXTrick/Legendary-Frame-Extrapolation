cmake_minimum_required(VERSION 3.27)

# 1. SDK Discovery: Tell CMake exactly where to look if the environment variable is missing
if(NOT DEFINED ENV{GEODE_SDK})
    if(APPLE OR UNIX)
        set(GEODE_SDK_PATH "$ENV{HOME}/.geode/sdk")
    else()
        set(GEODE_SDK_PATH "$ENV{LOCALAPPDATA}/Geode/sdk")
    endif()
    set(Geode_DIR "${GEODE_SDK_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK_PATH}")
endif()

# 2. Find the Geode Package
find_package(Geode REQUIRED CONFIG)

# 3. Project Definition
project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 4. Source Files: Finds everything in your src/ folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

# 5. Create the Mod
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 6. Geode Setup: This handles all the platform-specific magic (iOS, Android, etc.)
setup_geode_mod(${PROJECT_NAME})
