


include_directories("${PROJECT_SOURCE_DIR}/../../VixenEngine/include"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/directx")



file(GLOB VGRAPHICS_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/*.h)
file(GLOB VGRAPHICS_DX_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vgraphics/directx/*.h)

file(GLOB VGRAPHICS_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgraphics/*.cpp)
file(GLOB VGRAPHICS_DX_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vgraphics/directx/*.cpp)


source_group("Header Files\\directx" FILES ${VGRAPHICS_DX_INC})
source_group("Source Files\\directx" FILES ${VGRAPHICS_DX_SRC})

add_library(vgraphics SHARED ${VGRAPHICS_INC} ${VGRAPHICS_DX_INC} ${VGRAPHICS_SRC} ${VGRAPHICS_DX_SRC})

target_compile_definitions(vgraphics PRIVATE UNICODE _UNICODE VIX_DIRECTX_BUILD VIX_NONCLIENT_BUILD)

target_link_libraries(vgraphics PUBLIC vcore d3d11 d3dcompiler assimp::assimp freeimage::FreeImage)