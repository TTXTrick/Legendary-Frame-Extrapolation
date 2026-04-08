cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# The 'build-geode-mod' action will automatically provide the Geode_DIR
find_package(Geode REQUIRED CONFIG)

# Finds .cpp files in the src/ folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Links the mod and sets up the .geode package
setup_geode_mod(${PROJECT_NAME})
