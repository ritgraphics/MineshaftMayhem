include_directories("${PROJECT_SOURCE_DIR}/../../VixenEngine/include"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgame"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/Assimp/include"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/FreeImage"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/SDL2/include"
                    			"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/lua/include"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/luaintf/"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/bullet3/src"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/libcurl/include"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/jsoncpp/include")

file(GLOB VGAME_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgame/*.h)
file(GLOB VGAME_BULLET_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgame/vix_bullet*)
file(GLOB VGAME_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgame/*.cpp)
file(GLOB VGAME_BULLET_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgame/vix_bullet*)


source_group("Header Files\\bullet" FILES ${VGAME_BULLET_INC})
source_group("Source Files\\bullet" FILES ${VGAME_BULLET_SRC})

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
	set(PLATFORM_TOOLSET "VS2013")
else()
	set(PLATFORM_TOOLSET "VS2015")
endif()


add_definitions(-DLUAINTF_HEADERS_ONLY)
add_definitions(-DVIX_DIRECTX_BUILD)
add_definitions(-DVIX_NOEXTERN_LUA)
add_definitions(-D_UNICODE)

link_directories(${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2/${PLATFORM_TOOLSET}/Debug/ 
                 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/Assimp/ 
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/FreeImage/
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/SDL2/
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/lua/
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/bullet3/
				 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/libcurl/
			 	 ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/jsoncpp/)

add_library(vgame SHARED ${VGAME_INC} ${VGAME_SRC})

target_compile_definitions(vgame PRIVATE VIX_NONCLIENT_BUILD)

target_link_libraries(vgame vcore vgraphics SDL2 lua tinyxml2 Assimp Freeimage BulletCollision BulletDynamics BulletSoftBody LinearMath libcurl_imp jsoncpp)