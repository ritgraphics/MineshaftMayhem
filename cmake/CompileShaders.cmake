
# Find DirectX Shader Compiler
find_program(DXC_COMPILER NAMES dxc REQUIRED)

function(CompileHLSLShaders SHADER_FILES)

    set(COMPILED_HLSL_BINARIES "")
    foreach (file ${SHADER_FILES})
        get_filename_component(name ${file} NAME_WLE)
        get_filename_component(directory ${file} DIRECTORY)
        get_filename_component(dirname ${directory} NAME_WLE)
        list(APPEND COMPILED_HLSL_BINARIES ${PROJECT_BINARY_DIR}/source/${dirname}/${name}VS.bin)
        list(APPEND COMPILED_HLSL_BINARIES ${PROJECT_BINARY_DIR}/source/${dirname}/${name}PS.bin)
        add_custom_command(
                OUTPUT "${PROJECT_BINARY_DIR}/source/${dirname}/${name}VS.bin"
                OUTPUT "${PROJECT_BINARY_DIR}/source/${dirname}/${name}PS.bin"
                COMMAND ${DXC_COMPILER} -T vs_6_6 -E VSMain ${file} -Fo ${PROJECT_BINARY_DIR}/source/${dirname}/${name}VS.bin
                COMMAND ${DXC_COMPILER} -T ps_6_6 -E PSMain ${file} -Fo ${PROJECT_BINARY_DIR}/source/${dirname}/${name}PS.bin
                COMMENT "Compiling ${name} to HLSL binary object files"
                DEPENDS ${file} ${directory})
    endforeach ()

    add_custom_target(CompileHLSLShaders
            DEPENDS "${COMPILED_HLSL_BINARIES}"
    )
endfunction()