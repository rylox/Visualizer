cmake_minimum_required(VERSION 3.16)
project(Visualizer)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/rtaudio)
add_subdirectory(external/glfw-3.3.2)
# AUTO_LOCATE_VULKAN - accepted value ON or OFF
# ON  - Use CMake to auto locate the Vulkan SDK.
# OFF - Vulkan SDK path can be specified manually. This is helpful to test the build on various Vulkan version.
option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)

if (AUTO_LOCATE_VULKAN)
    message(STATUS "Attempting auto locate Vulkan using CMake......")

    if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
        # Find Vulkan Path using CMake's Vulkan Module
        # This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
        # Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
        find_package(Vulkan REQUIRED)
    endif ()

    if (NOT Vulkan_FOUND)
        message(STATUS "Failed to locate Vulkan SDK automatically...")
    endif ()
endif ()

if (NOT Vulkan_FOUND OR NOT AUTO_LOCATE_VULKAN)
    message(STATUS "Attempting to locate Vulkan SDK using manual path......")
    set(VULKAN_SDK "C:/VulkanSDK")
    set(VULKAN_VERSION "1.2.162.1")
    set(VULKAN_PATH "${VULKAN_SDK}/${VULKAN_VERSION}")
    message(STATUS "Using manual specified path: ${VULKAN_PATH}")
endif ()

# Add any required preprocessor definitions here
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)

# vulkan-1 library for build Vulkan application.
set(VULKAN_LIB_LIST ${Vulkan_LIBRARY})

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Include Vulkan header files from Vulkan SDK
    include_directories(AFTER ${VULKAN_PATH}/Include)
    # Link directory for vulkan-1
    link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib;)
endif ()

include_directories(${Vulkan_INCLUDE_DIRS})

# Define include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Gather list of header and source files for compilation
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.*)
# Build project, give it a name and includes list of file to be compiled
add_executable(${PROJECT_NAME} ${CPP_FILES} ${HPP_FILES})

add_subdirectory(shaders)
add_dependencies(${PROJECT_NAME} Shaders)

target_link_libraries(${CMAKE_PROJECT_NAME} glfw ${VULKAN_LIB_LIST} rtaudio)