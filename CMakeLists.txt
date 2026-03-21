cmake_minimum_required(VERSION 3.27)

# 1. Get the path from the Environment Variable we saw in your logs
if(DEFINED ENV{GEODE_SDK})
    set(GEODE_ROOT "$ENV{GEODE_SDK}")
    message(STATUS "Geode Root: ${GEODE_ROOT}")
    
    # 2. Add the specific subfolders where GeodeConfig.cmake lives
    list(APPEND CMAKE_PREFIX_PATH 
        "${GEODE_ROOT}"
        "${GEODE_ROOT}/loader"
        "${GEODE_ROOT}/cmake"
    )
    
    # 3. Explicitly help CMake find the directory
    set(Geode_DIR "${GEODE_ROOT}")
endif()

# 4. Find Geode (using CONFIG mode to ensure it uses the Geode-provided logic)
find_package(Geode REQUIRED CONFIG)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 5. Build Logic
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
setup_geode_mod(${PROJECT_NAME})
