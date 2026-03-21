cmake_minimum_required(VERSION 3.27)

# 1. Ask the CLI directly where the SDK is (The most reliable way)
execute_process(
    COMMAND geode sdk path
    OUTPUT_VARIABLE GEODE_SDK_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

# 2. Use the path from the CLI, or fall back to the environment variable
if(GEODE_SDK_PATH)
    set(Geode_DIR "${GEODE_SDK_PATH}")
    message(STATUS "Geode SDK found via CLI: ${GEODE_SDK_PATH}")
elseif(DEFINED ENV{GEODE_SDK})
    set(Geode_DIR "$ENV{GEODE_SDK}")
    message(STATUS "Geode SDK found via Env: $ENV{GEODE_SDK}")
endif()

# 3. Find Geode
find_package(Geode REQUIRED CONFIG)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 4. Standard build logic
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
setup_geode_mod(${PROJECT_NAME})
