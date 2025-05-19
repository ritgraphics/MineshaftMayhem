cmake_minimum_required(VERSION 3.25)
project(MineshaftMayhem)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Version info
set (MineshaftMayhem_VERSION_MAJOR 0)
set (MineshaftMayhem_VERSION_MINOR 1)
set (MineshaftMayhem_VERSION_BUILD 1)

#configure header file to pass
#CMake settings to source code
configure_file (
    "${PROJECT_SOURCE_DIR}/../include/MineshaftMayhem.h.in"
    "${PROJECT_SOURCE_DIR}/../include/MineshaftMayhem.h"
)

find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(unofficial-inih CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)
find_package(Lua REQUIRED)


add_subdirectory("${PROJECT_SOURCE_DIR}/MineshaftMayhem")
