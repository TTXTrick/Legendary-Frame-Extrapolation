cmake_minimum_required(VERSION 3.27.9)

project(frame_extrapolation VERSION 1.0.0)

# Setup Geode SDK
find_package(Geode REQUIRED HINTS ${CMAKE_CURRENT_SOURCE_DIR}/geode)

# Add our source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the Geode mod target
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
