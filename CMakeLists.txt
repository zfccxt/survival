cmake_minimum_required(VERSION 3.21)
project(survival)

set(CMAKE_CONFIGURATION_TYPES Verbose Debug Profile Release Distribution)

set(CMAKE_CXX_FLAGS_VERBOSE "${CMAKE_CXX_FLAGS_DEBUG} -DCALCIUM_BUILD_DEBUG=1 -DCALCIUM_BUILD_VERBOSE=1")
set(CMAKE_EXE_LINKER_FLAGS_VERBOSE "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELEASE} -DCALCIUM_BUILD_PROFILE=1 -DCALCIUM_BUILD_RELEASE=1")
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DISTRIBUTION "${CMAKE_CXX_FLAGS_RELEASE} -DCALCIUM_BUILD_RELEASE=1 -DCALCIUM_BUILD_DISTRIBUTION=1")
set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTION "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCALCIUM_BUILD_DEBUG=1")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DCALCIUM_BUILD_RELEASE=1")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")

set(SOURCE_FILES src/main.cpp src/chunk.hpp src/chunk.cpp src/level.hpp src/level.cpp src/camera.hpp src/camera.cpp src/key_bindings.hpp src/key_bindings.cpp src/control_settings.hpp src/control_settings.cpp src/floor_tile.hpp src/floor_tile.cpp src/hud.hpp src/hud.cpp)
source_group("src" FILES ${SOURCE_FILES})

set(SHADER_FILES src/shaders/chunk_shader.vert.glsl src/shaders/chunk_shader.frag.glsl)
source_group("src/shaders" FILES ${SHADER_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SHADER_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_subdirectory(depend/calcium)
target_link_libraries(${PROJECT_NAME} PRIVATE calcium)
add_subdirectory(depend/clx_imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE clx_imgui)

target_include_directories(${PROJECT_NAME} PRIVATE src)

if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_GENERATE_SCHEME TRUE XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
if(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
  set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Add custom target - compile glsl shaders to spirv
set(GLSLANG_VALIDATOR "glslangValidator")
file(GLOB_RECURSE GLSL_SOURCE_FILES "src/shaders/*.glsl")
foreach(GLSL_FILE ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL_FILE} NAME)
  string(REGEX REPLACE "[.]glsl$" ".spv" SPIRV_FILE_NAME ${FILE_NAME})
  set(SPIRV_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/${SPIRV_FILE_NAME}")
  add_custom_command(
    OUTPUT ${SPIRV_FILE}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/"
    COMMAND ${GLSLANG_VALIDATOR} -V ${GLSL_FILE} -o ${SPIRV_FILE}
    DEPENDS ${GLSL_FILE})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV_FILE})
endforeach(GLSL_FILE)
add_custom_target(survival_shader_target DEPENDS ${SPIRV_BINARY_FILES})
add_dependencies(${PROJECT_NAME} survival_shader_target)
