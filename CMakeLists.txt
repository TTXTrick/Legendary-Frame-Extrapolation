cmake_minimum_required(VERSION 3.27.9)

# 1. THE CI FIX: Bridge the gap between the GitHub Runner and CMake.
# This ensures that Geode is found on Windows, macOS, and Linux (Android).
if(DEFINED ENV{GEODE_SDK})
    file(TO_CMAKE_PATH "$ENV{GEODE_SDK}" GEODE_SDK_PATH)
    set(Geode_DIR "${GEODE_SDK_PATH}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK_PATH}")
endif()

# 2. Load the Geode package. 
# Using CONFIG mode is more reliable for finding the SDK in CI environments.
find_package(Geode REQUIRED CONFIG)

# 3. Define the project. 
# This should match your mod.json name/id preferences.
project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 4. Automatically find all your source files in the src/ directory.
# This includes subfolders and header files.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h src/*.c)

# 5. Define the mod binary.
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 6. The "Magic" Geode function.
# This handles Android NDK toolchains, macOS Universal Binaries, 
# and Windows .lib linking automatically.
setup_geode_mod(${PROJECT_NAME})
