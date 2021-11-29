if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL AMD64)
    set(GLSL_COMPILER $ENV{VULKAN_SDK}/Bin/glslc.exe)
else()
    set(GLSL_COMPILER $ENV{VULKAN_SDK}/Bin32/glslc.exe)
endif()

file(GLOB_RECURSE GLSL_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/shaders/*.frag
        ${PROJECT_SOURCE_DIR}/shaders/*.vert)

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV ${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv)
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${GLSL_COMPILER} ${GLSL} -o ${SPIRV}
            DEPENDS ${GLSL}
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})