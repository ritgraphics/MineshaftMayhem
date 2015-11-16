


include_directories("${PROJECT_SOURCE_DIR}/../../VixenEngine/include"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/inih"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/jsoncpp"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/Assimp/include"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/FreeImage")




if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
	set(PLATFORM_TOOLSET "VS2013")
else()
	set(PLATFORM_TOOLSET "VS2015")
endif()


file(GLOB VGRAPHICS_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/*.h)
file(GLOB VGRAPHICS_DX_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/directx/*.h)

file(GLOB VGRAPHICS_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgraphics/*.cpp)
file(GLOB VGRAPHICS_DX_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgraphics/directx/*.cpp)


source_group("Header Files\\directx" FILES ${VGRAPHICS_DX_INC})
source_group("Source Files\\directx" FILES ${VGRAPHICS_DX_SRC})

link_directories(${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2/${PLATFORM_TOOLSET}/Debug/ 
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/jsoncpp/
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/Assimp/ 
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/FreeImage/)

add_library(vgraphics SHARED ${VGRAPHICS_INC} ${VGRAPHICS_DX_INC} ${VGRAPHICS_SRC} ${VGRAPHICS_DX_SRC})


add_definitions(-D_UNICODE)
add_definitions(-DVIX_DIRECTX_BUILD)

target_compile_definitions(vgraphics PRIVATE VIX_NONCLIENT_BUILD)

target_link_libraries(vgraphics vcore d3d11 d3dcompiler Assimp tinyxml2 jsoncpp Freeimage)