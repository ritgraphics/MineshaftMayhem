

include_directories("${PROJECT_SOURCE_DIR}/../../VixenEngine/include"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore"
                    "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/tinyxml2"
	            "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/jsoncpp/include"
		    "${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/inih")
					
file(GLOB VCORE_INC ${PROJECT_SOURCE_DIR}/../../VixenEngine/include/vcore/*.h)
file(GLOB VCORE_SRC ${PROJECT_SOURCE_DIR}/../../VixenEngine/source/vcore/*.cpp ${PROJECT_SOURCE_DIR}/../../VixenEngine/dependencies/x64/inih/*.c)



add_library(vcore SHARED ${VCORE_INC} ${VCORE_SRC})
target_compile_definitions(vcore PRIVATE UNICODE)
target_link_libraries(vcore PUBLIC SDL2::SDL2 tinyxml2::tinyxml2 JsonCpp::JsonCpp unofficial::inih::libinih)

target_compile_definitions(vcore PRIVATE VIX_NONCLIENT_BUILD)
