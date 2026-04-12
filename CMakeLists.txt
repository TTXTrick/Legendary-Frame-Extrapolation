cmake_minimum_required(VERSION 3.21)

# 1. Standard C++ Setup
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(ttxtrick_legendary_frame_extrapolation VERSION 1.0.0)

# 2. Find Geode (The correct way for CI)
find_package(Geode REQUIRED CONFIG)

# 3. Include CPM (For UIBuilder and GDReplayFormat)
# This snippet automatically downloads CPM so you don't need the .cmake file
set(CPM_DOWNLOAD_VERSION 0.38.2)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    message(STATUS "Downloading CPM.cmake...")
    file(DOWNLOAD "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake"
         "${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()
include("${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

# 4. Define your Mod Library
add_library(${PROJECT_NAME} SHARED src/main.cpp)

# 5. Add Subdirectories (Ensure 'gd-sim' folder exists in your root!)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gd-sim/CMakeLists.txt")
    add_subdirectory(gd-sim)
endif()

# 6. Fetch External Dependencies
CPMAddPackage("gh:camila314/UIBuilder#main")
CPMAddPackage("gh:maxnut/GDReplayFormat#gdr2")

# 7. Geode Macro (Must be called before custom linking/options)
setup_geode_mod(${PROJECT_NAME})

# 8. Custom Compilation Logic
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG_MODE=1>)

# Optimization flags (High performance)
target_compile_options(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Debug>:-g> 
    $<$<CONFIG:Release>:-O3 -fno-math-errno -fno-trapping-math -fomit-frame-pointer>
    -fvisibility=hidden
)

# 9. Linking
# Note: UIBuilder and libGDR must be valid target names from the CPM packages
target_link_libraries(${PROJECT_NAME} 
    gd-sim 
    UIBuilder 
    libGDR
)

# 10. Apple Stripping
if (APPLE)
    add_custom_target(strip_binary ALL
        COMMAND $<$<CONFIG:Release>:strip -x $<TARGET_FILE:${PROJECT_NAME}>>
        DEPENDS ${PROJECT_NAME}
    )
endif()
