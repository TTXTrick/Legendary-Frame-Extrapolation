cmake_minimum_required(VERSION 3.27)

# This line is the magic fix for "GeodeConfig.cmake not found"
# It tells CMake to look in the folder the Action just installed Geode into.
if(DEFINED ENV{GEODE_SDK})
    set(Geode_DIR "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

setup_geode_mod(${PROJECT_NAME})
