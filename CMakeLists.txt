cmake_minimum_required(VERSION 3.25)
project(MineshaftMayhem)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Version info
set (MineshaftMayhem_VERSION_MAJOR 0)
set (MineshaftMayhem_VERSION_MINOR 1)
set (MineshaftMayhem_VERSION_BUILD 1)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# TODO: Compile HLSL shaders
include(CompileShaders)
file(GLOB_RECURSE HLSL_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/assets/Shaders/DirectX/*.hlsl)
#CompileHLSLShaders("${HLSL_SHADERS}")

#configure header file to pass
#CMake settings to source code
configure_file (
    "${PROJECT_SOURCE_DIR}/include/MineshaftMayhem.h.in"
    "${PROJECT_SOURCE_DIR}/include/MineshaftMayhem.h"
)

find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(directxtk CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(unofficial-inih CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)
find_package(Lua REQUIRED)

file(GLOB FONT_FILES ${PROJECT_SOURCE_DIR}/assets/Fonts/*.fnt)
file(GLOB MODEL_FILES ${PROJECT_SOURCE_DIR}/assets/Models/*.mdl)
file(GLOB MATERIAL_FILES ${PROJECT_SOURCE_DIR}/assets/Materials/*.vmt)
file(GLOB PREFAB_FILES ${PROJECT_SOURCE_DIR}/assets/Prefabs/*.pfb)
file(GLOB SCENE_FILES ${PROJECT_SOURCE_DIR}/assets/Scenes/*.scene)
file(GLOB SCENE_CONFIG ${PROJECT_SOURCE_DIR}/assets/Scenes/scenes.config)
file(GLOB SCRIPT_FILES ${PROJECT_SOURCE_DIR}/assets/Scripts/*.lua)
file(GLOB HLSL_VS_FILES ${PROJECT_SOURCE_DIR}/assets/Shaders/DirectX/*_VS.hlsl)
file(GLOB HLSL_PS_FILES ${PROJECT_SOURCE_DIR}/assets/Shaders/DirectX/*_PS.hlsl)
file(GLOB GLSL_FILES ${PROJECT_SOURCE_DIR}/assets/Shaders/OpenGL/*.glsl)
file(GLOB TEXTURE_FILES ${PROJECT_SOURCE_DIR}/assets/Textures/*.png ${PROJECT_SOURCE_DIR}/assets/Textures/*.jpg)

set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_TYPE Pixel)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_ENTRYPOINT main)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_FLAGS "/DFLAGS_ADDED /Fh \"$(OutDir)%(Filename).h\"")

set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_TYPE Vertex)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_ENTRYPOINT main)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_FLAGS "/DFLAGS_ADDED /Fh \"$(OutDir)%(Filename).h\"")

source_group("Asset Files\\Models" FILES ${MODEL_FILES})
source_group("Asset Files\\Materials" FILES ${MATERIAL_FILES})
source_group("Asset Files\\Fonts" FILES ${FONT_FILES})
source_group("Asset Files\\Prefabs" FILES ${PREFAB_FILES})
source_group("Asset Files\\Scenes" FILES ${SCENE_FILES} ${SCENE_CONFIG})
source_group("Asset Files\\Scripts" FILES ${SCRIPT_FILES})
source_group("Asset Files\\Shaders\\HLSL\\Vertex Shaders" FILES ${HLSL_VS_FILES})
source_group("Asset Files\\Shaders\\HLSL\\Pixel Shaders" FILES ${HLSL_PS_FILES})
source_group("Asset Files\\Shaders\\GLSL" FILES ${GLSL_FILES})
source_group("Asset Files\\Textures" FILES ${TEXTURE_FILES})

set(RESOURCE_FILES ${MODEL_FILES} ${FONT_FILES} ${PREFAB_FILES} ${SCENE_FILES} ${SCENE_CONFIG} ${SCRIPT_FILES} ${HLSL_VS_FILES} ${HLSL_PS_FILES} ${GLSL_FILES} ${TEXTURE_FILES} ${MATERIAL_FILES})

file(GLOB VCORE_INC ${PROJECT_SOURCE_DIR}/VixenEngine/include/vcore/*.h)
file(GLOB VCORE_SRC ${PROJECT_SOURCE_DIR}/VixenEngine/source/vcore/*.cpp)

file(GLOB VGRAPHICS_INC ${PROJECT_SOURCE_DIR}/VixenEngine/include/vgraphics/*.h)
file(GLOB VGRAPHICS_DX_INC ${PROJECT_SOURCE_DIR}/VixenEngine/include/vgraphics/directx/*.h)
file(GLOB VGRAPHICS_SRC ${PROJECT_SOURCE_DIR}/VixenEngine/source/vgraphics/*.cpp)
file(GLOB VGRAPHICS_DX_SRC ${PROJECT_SOURCE_DIR}/VixenEngine/source/vgraphics/directx/*.cpp)

file(GLOB VGAME_INC ${PROJECT_SOURCE_DIR}/VixenEngine/include/vgame/*.h)
file(GLOB VGAME_BULLET_INC ${PROJECT_SOURCE_DIR}/VixenEngine/include/vgame/vix_bullet*)
file(GLOB VGAME_SRC ${PROJECT_SOURCE_DIR}/VixenEngine/source/vgame/*.cpp)
file(GLOB VGAME_BULLET_SRC ${PROJECT_SOURCE_DIR}/VixenEngine/source/vgame/vix_bullet*)


add_executable(MineshaftMayhem WIN32
    ${PROJECT_SOURCE_DIR}/source/main.cpp
    ${VCORE_INC}
    ${VCORE_SRC}
    ${VGRAPHICS_INC}
    ${VGRAPHICS_DX_INC}
    ${VGRAPHICS_SRC}
    ${VGRAPHICS_DX_SRC}
    ${VGAME_INC}
    ${VGAME_BULLET_INC}
    ${VGAME_SRC}
    ${VGAME_BULLET_SRC}
    ${RESOURCE_FILES}
    "source/GameTimer.hpp"
    "source/GameTimer.cpp"
    "source/Game.hpp"
    "source/Game.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE
                    "${PROJECT_SOURCE_DIR}/include"
					"${PROJECT_SOURCE_DIR}/VixenEngine/include/"
					"${PROJECT_SOURCE_DIR}/VixenEngine/include/vcore"
					"${PROJECT_SOURCE_DIR}/VixenEngine/include/vgraphics"
					"${PROJECT_SOURCE_DIR}/VixenEngine/include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/VixenEngine/include/vgame"
                    "${PROJECT_SOURCE_DIR}/VixenEngine/dependencies/LuaIntf")

add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/vixen.env $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/vixen.config $<TARGET_FILE_DIR:MineshaftMayhem>)

target_compile_definitions(MineshaftMayhem PRIVATE LUAINTF_HEADERS_ONLY UNICODE _UNICODE VIX_STATIC VIX_DIRECTX_BUILD)

target_link_libraries(MineshaftMayhem PRIVATE
    SDL3::SDL3
    Microsoft::DirectXTK
    fmt::fmt
    tinyxml2::tinyxml2
    JsonCpp::JsonCpp
    unofficial::inih::libinih
    ${LUA_LIBRARIES}
    ${BULLET_LIBRARIES}
    d3d11
    d3dcompiler
    assimp::assimp
    freeimage::FreeImage
)
