cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# The Build Action injects the path for this automatically.
find_package(Geode REQUIRED CONFIG)

# Find the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Links everything and creates the .geode file
setup_geode_mod(${PROJECT_NAME})
