cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# Let the GitHub Action handle the path injection automatically
find_package(Geode REQUIRED CONFIG)

# Source discovery
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Geode macro
setup_geode_mod(${PROJECT_NAME})
