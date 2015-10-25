

include_directories("${PROJECT_SOURCE_DIR}/../../VixenEngine/include"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2")
					
file(GLOB VCORE_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore/*.h)
file(GLOB VCORE_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vcore/*.cpp)


if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
	set(PLATFORM_TOOLSET "VS2013")
else()
	set(PLATFORM_TOOLSET "VS2015")
endif()

add_definitions(-D_UNICODE)

link_directories(${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2/${PLATFORM_TOOLSET}/Debug/)

add_library(vcore SHARED ${VCORE_INC} ${VCORE_SRC})

target_compile_definitions(vcore PRIVATE VIX_NONCLIENT_BUILD)


target_link_libraries(vcore tinyxml2)