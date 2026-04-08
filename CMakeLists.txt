cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# The Build Action handles all the pathing logic behind the scenes.
find_package(Geode REQUIRED CONFIG)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

setup_geode_mod(${PROJECT_NAME})
