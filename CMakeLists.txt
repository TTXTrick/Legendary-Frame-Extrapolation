cmake_minimum_required(VERSION 3.27.9)

# Define the project name and version
project(frame_extrapolation VERSION 1.0.0)

# THE FIX: This tells CMake to look in the environment variable 
# created by the Geode CLI on the GitHub runner.
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

# Now find the Geode package
find_package(Geode REQUIRED)

# We explicitly name src/main.cpp to ensure the CI finds the source
# Make sure your main.cpp is located in a folder named 'src'
add_library(${PROJECT_NAME} SHARED src/main.cpp)

# Use the Geode helper to setup the mod and package it
setup_geode_mod(${PROJECT_NAME})
