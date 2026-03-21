cmake_minimum_required(VERSION 3.27)

# 1. Force CMake to look exactly where the logs say the SDK is
set(GEODE_SDK_ROOT "$ENV{GEODE_SDK}")

# 2. If the SDK is there, manually add its cmake folder to the search path
if(EXISTS "${GEODE_SDK_ROOT}/cmake")
    list(APPEND CMAKE_MODULE_PATH "${GEODE_SDK_ROOT}/cmake")
    set(Geode_DIR "${GEODE_SDK_ROOT}")
    message(STATUS "Manually pointing to Geode at: ${GEODE_SDK_ROOT}")
endif()

# 3. Use the REQUIRED CONFIG flags to ensure it loads GeodeConfig.cmake
find_package(Geode REQUIRED CONFIG HINTS "${GEODE_SDK_ROOT}")

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 4. Source discovery
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 5. This is the function provided by Geode's cmake files
setup_geode_mod(${PROJECT_NAME})
