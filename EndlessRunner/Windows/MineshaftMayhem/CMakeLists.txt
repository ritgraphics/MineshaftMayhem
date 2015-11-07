
include_directories("${PROJECT_SOURCE_DIR}/../include/"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/include/"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgame"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/Assimp/include"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/FreeImage"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/SDL2/include"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/lua/include"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/luaintf/")

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
	set(PLATFORM_TOOLSET "VS2013")
else()
	set(PLATFORM_TOOLSET "VS2015")
endif()


add_definitions(-D_UNICODE)

link_directories("${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2/${PLATFORM_TOOLSET}/Debug/"
				 "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/Assimp/"
                 "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/FreeImage/"
				 "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/SDL2/"
				 "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/lua/")
				 
file(GLOB FONT_FILES ${PROJECT_SOURCE_DIR}/../assets/Fonts/*.fnt)
file(GLOB MODEL_FILES ${PROJECT_SOURCE_DIR}/../assets/Models/*.mdl)
file(GLOB PREFAB_FILES ${PROJECT_SOURCE_DIR}/../assets/Prefabs/*.pfb)
file(GLOB SCENE_FILES ${PROJECT_SOURCE_DIR}/../assets/Scenes/*.scene)
file(GLOB MATERIAL_FILES ${PROJECT_SOURCE_DIR}/../assets/Materials/*.vmt)
file(GLOB SCENE_CONFIG ${PROJECT_SOURCE_DIR}/../assets/Scenes/scenes.config)
file(GLOB SCRIPT_FILES ${PROJECT_SOURCE_DIR}/../assets/Scripts/*.lua)
file(GLOB HLSL_VS_FILES ${PROJECT_SOURCE_DIR}/../assets/Shaders/DirectX/*_VS.hlsl)
file(GLOB HLSL_PS_FILES ${PROJECT_SOURCE_DIR}/../assets/Shaders/DirectX/*_PS.hlsl)
file(GLOB GLSL_FILES ${PROJECT_SOURCE_DIR}/../assets/Shaders/OpenGL/*.glsl)
file(GLOB TEXTURE_FILES ${PROJECT_SOURCE_DIR}/../assets/Textures/*.png ${PROJECT_SOURCE_DIR}/../assets/Textures/*.jpg)

set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_TYPE Pixel)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_ENTRYPOINT main)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_FLAGS "/DFLAGS_ADDED /Fh \"$(OutDir)%(Filename).h\"")

set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_TYPE Vertex)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_ENTRYPOINT main)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_FLAGS "/DFLAGS_ADDED /Fh \"$(OutDir)%(Filename).h\"")

source_group("Asset Files\\Models" FILES ${MODEL_FILES})
source_group("Asset Files\\Fonts" FILES ${FONT_FILES})
source_group("Asset Files\\Prefabs" FILES ${PREFAB_FILES})
source_group("Asset Files\\Scenes" FILES ${SCENE_FILES} ${SCENE_CONFIG})
source_group("Asset Files\\Scripts" FILES ${SCRIPT_FILES})
source_group("Asset Files\\Materials" FILES ${MATERIAL_FILES})
source_group("Asset Files\\Shaders\\HLSL" FILES ${HLSL_VS_FILES} ${HLSL_PS_FILES})
source_group("Asset Files\\Shaders\\GLSL" FILES ${GLSL_FILES})
source_group("Asset Files\\Textures" FILES ${TEXTURE_FILES})

set(RESOURCE_FILES ${MODEL_FILES} ${FONT_FILES} ${PREFAB_FILES} ${SCENE_FILES} ${SCENE_CONFIG} ${SCRIPT_FILES} ${HLSL_VS_FILES} ${HLSL_PS_FILES} ${GLSL_FILES} ${TEXTURE_FILES} ${MATERIAL_FILES})

add_executable(MineshaftMayhem ${PROJECT_SOURCE_DIR}/../source/main.cpp ${RESOURCE_FILES})



add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/vixen.env $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/vixen.config $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   $(SolutionDir)vcore/$(Configuration)/vcore.dll $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   $(SolutionDir)vgraphics/$(Configuration)/vgraphics.dll $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   $(SolutionDir)vgame/$(Configuration)/vgame.dll $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/$(Platform)/Assimp/assimp.dll $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/$(Platform)/tinyxml2/${PLATFORM_TOOLSET}/$(Configuration)/tinyxml2.dll $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/$(Platform)/lua/lua.dll $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/$(Platform)/FreeImage/FreeImage.dll $<TARGET_FILE_DIR:MineshaftMayhem>)
add_custom_command(TARGET MineshaftMayhem POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/$(Platform)/SDL2/SDL2.dll $<TARGET_FILE_DIR:MineshaftMayhem>)

target_compile_definitions(MineshaftMayhem PRIVATE VIX_DIRECTX_BUILD)

target_link_libraries(MineshaftMayhem vcore vgraphics vgame SDL2 lua tinyxml2 Assimp FreeImage)