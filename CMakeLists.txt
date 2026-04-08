cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 1. Ask the Geode CLI exactly where the SDK is installed
execute_process(
    COMMAND geode sdk path
    OUTPUT_VARIABLE GEODE_CLI_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

message(STATUS "Geode CLI reports SDK at: ${GEODE_CLI_PATH}")

# 2. Tell CMake to ONLY look in that exact folder.
set(Geode_DIR "${GEODE_CLI_PATH}")
find_package(Geode REQUIRED CONFIG)

# 3. Standard Build Logic
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
setup_geode_mod(${PROJECT_NAME})
