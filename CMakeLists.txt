cmake_minimum_required(VERSION 3.27)

# --- DEBUG: Print where we are looking ---
message(STATUS "Checking for Geode SDK...")
message(STATUS "Env GEODE_SDK: $ENV{GEODE_SDK}")

# 1. Manually check the most common places Geode hides on GitHub Runners
set(GEODE_SEARCH_PATHS
    "$ENV{GEODE_SDK}"               # Standard Env Var
    "$ENV{HOME}/.geode/sdk"         # Mac/Linux default
    "$ENV{LOCALAPPDATA}/Geode/sdk"  # Windows default
    "D:/a/${PROJECT_NAME}/${PROJECT_NAME}/geode-sdk" # Github Windows workspace
)

# 2. Force CMake to find the package using those specific paths
find_package(Geode REQUIRED CONFIG HINTS ${GEODE_SEARCH_PATHS})

# --- DEBUG: Confirm if found ---
message(STATUS "Geode_DIR found at: ${Geode_DIR}")

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 3. Find source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 4. Standard Geode setup
setup_geode_mod(${PROJECT_NAME})
