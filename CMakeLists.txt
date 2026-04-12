cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(ttxtrick_legendary_frame_extrapolation VERSION 1.0.0)

# 1. FIND GEODE (With explicit hints for GitHub Actions)
find_package(Geode REQUIRED CONFIG HINTS "$ENV{GEODE_SDK}")

# 2. CPM SETUP (Required for UIBuilder and libGDR)
set(CPM_DOWNLOAD_VERSION 0.38.2)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    file(DOWNLOAD "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake"
         "${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()
include("${CMAKE_BINARY_DIR}/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

# 3. DEFINE MOD
add_library(${PROJECT_NAME} SHARED src/main.cpp)

# 4. DEPENDENCIES
# Using an IF check so it doesn't crash if the folder is missing during testing
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gd-sim/CMakeLists.txt")
    add_subdirectory(gd-sim)
endif()

CPMAddPackage("gh:camila314/UIBuilder#main")
CPMAddPackage("gh:maxnut/GDReplayFormat#gdr2")

# 5. GEODE SETUP
setup_geode_mod(${PROJECT_NAME})

# 6. COMPILER OPTIONS
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG_MODE=1>)
target_compile_options(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Debug>:-g> 
    -O3 -fno-math-errno -fno-trapping-math -fvisibility=hidden -fomit-frame-pointer
)

# 7. LINKING (Ensure target names are correct!)
# Note: If gd-sim is missing, this line will cause an error. 
# Only include it if gd-sim is actually in your repo.
target_link_libraries(${PROJECT_NAME} 
    gd-sim 
    UIBuilder 
    libGDR
)

# 8. APPLE STRIP
if (APPLE)
    add_custom_target(strip_binary ALL
        COMMAND $<$<CONFIG:Release>:strip -x $<TARGET_FILE:${PROJECT_NAME}>>
        DEPENDS ${PROJECT_NAME}
    )
endif()
