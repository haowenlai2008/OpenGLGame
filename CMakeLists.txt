cmake_minimum_required(VERSION 3.20)

project(OpenGLGame VERSION 1.0.0 LANGUAGES C CXX)

option(OPENGLGAME_USE_SHARED_DEPS "Use shared third-party libraries when available" OFF)
option(OPENGLGAME_ENABLE_FETCHCONTENT "Allow CMake to fetch missing third-party dependencies" OFF)
option(OPENGLGAME_COPY_RUNTIME_DLLS "Copy shared dependency DLLs beside the executable" ON)
option(OPENGLGAME_BUILD_TESTS "Build lightweight non-graphical tests" ON)

set(OPENGLGAME_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Engine/external" CACHE PATH
    "Root directory containing local third-party dependencies")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include(GNUInstallDirs)
include(cmake/Dependencies.cmake)

file(GLOB_RECURSE OPENGLGAME_ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE OPENGLGAME_ENGINE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/opengl_game/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/opengl_game/*.hpp")
list(REMOVE_ITEM OPENGLGAME_ENGINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/app/Application.cpp")

add_library(opengl_game_engine STATIC
    ${OPENGLGAME_ENGINE_SOURCES}
    ${OPENGLGAME_ENGINE_HEADERS}
    "${CMAKE_CURRENT_SOURCE_DIR}/Engine/external/source/glad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Engine/external/source/stb_image.cpp")
add_library(opengl_game::engine ALIAS opengl_game_engine)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PREFIX "src"
    FILES ${OPENGLGAME_ENGINE_SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PREFIX "include"
    FILES ${OPENGLGAME_ENGINE_HEADERS})
source_group("ThirdParty\\GLAD" FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/Engine/external/source/glad.c")
source_group("ThirdParty\\stb" FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/Engine/external/source/stb_image.cpp")

target_include_directories(opengl_game_engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(opengl_game_engine SYSTEM PUBLIC
    "${OPENGLGAME_ASSIMP_INCLUDE_DIR}"
    "${OPENGLGAME_DEPS_INCLUDE_DIR}"
    "${OPENGLGAME_DEPS_BULLET_INCLUDE_DIR}")
target_compile_definitions(opengl_game_engine PUBLIC
    NOMINMAX WIN32_LEAN_AND_MEAN GLFW_INCLUDE_NONE)

if(MSVC)
    target_compile_options(opengl_game_engine PRIVATE /W4 /permissive- /Zc:__cplusplus)
    target_compile_definitions(opengl_game_engine PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(opengl_game_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(opengl_game_engine PUBLIC
    OpenGL::GL opengl_game::glfw opengl_game::bullet opengl_game::assimp)

add_executable(opengl_game "${CMAKE_CURRENT_SOURCE_DIR}/src/app/Application.cpp")
add_executable(opengl_game::app ALIAS opengl_game)
target_link_libraries(opengl_game PRIVATE opengl_game::engine)
set_target_properties(opengl_game opengl_game_engine PROPERTIES FOLDER "OpenGLGame")

if(CMAKE_CONFIGURATION_TYPES)
    foreach(_config IN LISTS CMAKE_CONFIGURATION_TYPES)
        string(TOUPPER "${_config}" _config_upper)
        set_target_properties(opengl_game PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${_config_upper} "${CMAKE_BINARY_DIR}/bin/${_config}")
    endforeach()
endif()

add_custom_command(TARGET opengl_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Resources"
        "$<TARGET_FILE_DIR:opengl_game>/Resources"
    COMMENT "Copying renderer resources")

if(OPENGLGAME_COPY_RUNTIME_DLLS)
    opengl_game_copy_runtime_dependencies(opengl_game)
endif()

if(OPENGLGAME_BUILD_TESTS)
    enable_testing()
    add_executable(opengl_game_header_smoke tests/header_smoke.cpp)
    target_link_libraries(opengl_game_header_smoke PRIVATE opengl_game::engine)
    set_target_properties(opengl_game_header_smoke PROPERTIES FOLDER "OpenGLGame/Tests")

    add_executable(opengl_game_resource_test
        tests/resource_path_test.cpp
        src/core/ResourceLocator.cpp)
    target_include_directories(opengl_game_resource_test PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include")
    add_test(NAME resource_path_test COMMAND opengl_game_resource_test)
endif()

install(TARGETS opengl_game opengl_game_engine
    RUNTIME DESTINATION . LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY Engine/Resources DESTINATION .)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
