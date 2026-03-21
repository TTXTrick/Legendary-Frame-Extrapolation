cmake_minimum_required(VERSION 3.27.9)

# We are telling CMake: "Don't guess. Look in EVERY one of these spots."
set(POTENTIAL_GEODE_PATHS
    "$ENV{GEODE_SDK}"
    "$ENV{HOME}/.geode/sdk"
    "/home/runner/.geode/sdk"
    "/Users/runner/.geode/sdk"
    "C:/Users/runner/.geode/sdk"
)

# Force find_package to use our list and ignore system defaults that might be empty
find_package(Geode REQUIRED CONFIG PATHS ${POTENTIAL_GEODE_PATHS} NO_DEFAULT_PATH)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# Automatically finds your code in the src folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# This handles the cross-compilation for iOS/Android/Windows/Mac
setup_geode_mod(${PROJECT_NAME})
