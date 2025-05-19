include_directories("${PROJECT_SOURCE_DIR}/../../VixenEngine/include"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgame"
					"${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/LuaIntf/")

file(GLOB VGAME_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgame/*.h)
file(GLOB VGAME_BULLET_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgame/vix_bullet*)
file(GLOB VGAME_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgame/*.cpp)
file(GLOB VGAME_BULLET_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgame/vix_bullet*)


source_group("Header Files\\bullet" FILES ${VGAME_BULLET_INC})
source_group("Source Files\\bullet" FILES ${VGAME_BULLET_SRC})

add_library(vgame SHARED ${VGAME_INC} ${VGAME_SRC})

target_compile_definitions(vgame PRIVATE UNICODE _UNICODE VIX_DIRECTX_BUILD LUAINTF_HEADERS_ONLY VIX_NONCLIENT_BUILD)
target_include_directories(vgame PRIVATE ${LUA_INCLUDE_DIRS})
target_link_libraries(vgame PUBLIC vcore vgraphics SDL2::SDL2 ${LUA_LIBRARIES} ${BULLET_LIBRARIES})

