cmake_minimum_required(VERSION 3.27)

project(LegendaryFrameExtrapolation VERSION 1.0.0)

# 1. Look for the SDK in EVERY possible location
set(SEARCH_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/geode-sdk"
    "${CMAKE_CURRENT_SOURCE_DIR}/geode"
    "$ENV{GEODE_SDK}"
    "$ENV{HOME}/.geode/sdk"
    "$ENV{LOCALAPPDATA}/Geode/sdk"
)

# 2. Try to find the package with those hints
find_package(Geode CONFIG HINTS ${SEARCH_PATHS})

# 3. If that STILL fails, try a direct include from the workspace
if(NOT Geode_FOUND)
    file(GLOB_RECURSE FOUND_GEODE_CMAKE "${CMAKE_CURRENT_SOURCE_DIR}/*GeodeConfig.cmake")
    if(FOUND_GEODE_CMAKE)
        get_filename_component(GEODE_DIR_FOUND "${FOUND_GEODE_CMAKE}" DIRECTORY)
        set(Geode_DIR "${GEODE_DIR_FOUND}")
        find_package(Geode REQUIRED CONFIG)
    else()
        message(FATAL_ERROR "Geode SDK not found in workspace or system. Paths searched: ${SEARCH_PATHS}")
    endif()
endif()

# 4. Standard build
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
setup_geode_mod(${PROJECT_NAME})
