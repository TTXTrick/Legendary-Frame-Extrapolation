cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(ttxtrick_legendary_frame_extrapolation VERSION 1.0.0)

# 1. FORCE CMAKE TO FIND THE SDK
# We check if the environment variable exists, and if so, tell CMake exactly where it is.
if(DEFINED ENV{GEODE_SDK})
    set(Geode_DIR "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED CONFIG)

# 2. CPM SETUP (Only if you need UIBuilder/GDReplayFormat)
set(CPM_DOWNLOAD_VERSION 0.38.2)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    file(DOWNLOAD "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake"
         "${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()
include("${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

# 3. DEFINE YOUR MOD
add_library(${PROJECT_NAME} SHARED src/main.cpp)

# 4. EXTERNAL DEPENDENCIES (Comment out if not using yet)
# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gd-sim/CMakeLists.txt")
#    add_subdirectory(gd-sim)
# endif()
# CPMAddPackage("gh:camila314/UIBuilder#main")
# CPMAddPackage("gh:maxnut/GDReplayFormat#gdr2")

# 5. GEODE MACRO
setup_geode_mod(${PROJECT_NAME})

# 6. LINKING
# target_link_libraries(${PROJECT_NAME} gd-sim UIBuilder libGDR)
