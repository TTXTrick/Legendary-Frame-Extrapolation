cmake_minimum_required(VERSION 3.27.9)

project(frame_extrapolation VERSION 1.0.0)

# FORCE CMAKE TO FIND THE SDK
# The Geode CLI sets the GEODE_SDK environment variable. 
# We convert it to a CMake path and add it to the search list.
if(DEFINED ENV{GEODE_SDK})
    file(TO_CMAKE_PATH "$ENV{GEODE_SDK}" GEODE_SDK_PATH)
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK_PATH}")
    set(Geode_DIR "${GEODE_SDK_PATH}")
endif()

# Also check for the Bindings path which is sometimes needed in CI
if(DEFINED ENV{GEODE_BINDINGS_REPO_PATH})
    file(TO_CMAKE_PATH "$ENV{GEODE_BINDINGS_REPO_PATH}" GEODE_BINDINGS_PATH)
    set(GEODE_BINDINGS_REPOSITORY "${GEODE_BINDINGS_PATH}")
endif()

# Now attempt to find the package
find_package(Geode REQUIRED)

# Setup the source files
# Ensure your main.cpp is in a folder named 'src'
add_library(${PROJECT_NAME} SHARED src/main.cpp)

# Finalize the Geode mod setup
setup_geode_mod(${PROJECT_NAME})
