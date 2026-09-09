include_guard(GLOBAL)

if(NOT WIN32)
    message(FATAL_ERROR
        "This repository currently ships Windows prebuilt dependencies. "
        "Add a platform-specific dependency mapping before building elsewhere.")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(_openglgame_arch x64)
else()
    set(_openglgame_arch x86)
endif()

set(_openglgame_config_root "${OPENGLGAME_DEPS_ROOT}/${_openglgame_arch}")
set(_openglgame_include_dir "${OPENGLGAME_DEPS_ROOT}/include")
set(_openglgame_assimp_include_dir "${_openglgame_include_dir}")
if(EXISTS "${_openglgame_config_root}/include/assimp")
    set(_openglgame_assimp_include_dir "${_openglgame_config_root}/include")
endif()
set(_openglgame_bullet_include_dir "${OPENGLGAME_DEPS_ROOT}/source/bullet")
set(OPENGLGAME_DEPS_INCLUDE_DIR "${_openglgame_include_dir}" CACHE INTERNAL "")
set(OPENGLGAME_ASSIMP_INCLUDE_DIR "${_openglgame_assimp_include_dir}" CACHE INTERNAL "")
set(OPENGLGAME_DEPS_BULLET_INCLUDE_DIR "${_openglgame_bullet_include_dir}" CACHE INTERNAL "")

if(OPENGLGAME_USE_SHARED_DEPS)
    message(STATUS "OpenGLGame dependency mode: shared/import libraries preferred")
else()
    message(STATUS "OpenGLGame dependency mode: static libraries preferred")
endif()

foreach(_required_path IN ITEMS
    "${_openglgame_include_dir}/glad.h"
    "${_openglgame_include_dir}/glfw3.h"
    "${_openglgame_bullet_include_dir}/btBulletDynamicsCommon.h")
    if(NOT EXISTS "${_required_path}")
        message(FATAL_ERROR "Missing local dependency file: ${_required_path}")
    endif()
endforeach()

find_package(OpenGL REQUIRED)

function(_openglgame_find_library out_target name)
    find_library(_openglgame_release_${name}
        NAMES "${name}"
        PATHS "${_openglgame_config_root}/Release/lib"
        NO_DEFAULT_PATH)
    find_library(_openglgame_debug_${name}
        NAMES "${name}"
        PATHS "${_openglgame_config_root}/Debug/lib"
        NO_DEFAULT_PATH)
    if(NOT _openglgame_release_${name} AND NOT _openglgame_debug_${name})
        message(FATAL_ERROR
            "Could not find local ${name} for ${_openglgame_arch}. "
            "Expected it below ${_openglgame_config_root}/{Debug,Release}/lib. "
            "Set OPENGLGAME_DEPS_ROOT to a matching dependency root, "
            "or provide a package-manager build.")
    endif()
    if(NOT _openglgame_release_${name})
        set(_openglgame_release_${name} "${_openglgame_debug_${name}}")
    endif()
    if(NOT _openglgame_debug_${name})
        set(_openglgame_debug_${name} "${_openglgame_release_${name}}")
    endif()
    set(${out_target}_RELEASE "${_openglgame_release_${name}}" PARENT_SCOPE)
    set(${out_target}_DEBUG "${_openglgame_debug_${name}}" PARENT_SCOPE)
endfunction()

function(_openglgame_make_imported target release_path debug_path)
    add_library(${target} UNKNOWN IMPORTED GLOBAL)
    set_target_properties(${target} PROPERTIES
        IMPORTED_CONFIGURATIONS "Debug;Release"
        IMPORTED_LOCATION_RELEASE "${release_path}"
        IMPORTED_LOCATION_DEBUG "${debug_path}")
endfunction()

_openglgame_find_library(_openglgame_glfw glfw3)
_openglgame_find_library(_openglgame_bullet_collision BulletCollision)
_openglgame_find_library(_openglgame_bullet_dynamics BulletDynamics)
_openglgame_find_library(_openglgame_bullet_softbody BulletSoftBody)
_openglgame_find_library(_openglgame_linear_math LinearMath)
_openglgame_find_library(_openglgame_assimp assimp-vc140-mt)

_openglgame_make_imported(opengl_game::glfw
    "${_openglgame_glfw_RELEASE}" "${_openglgame_glfw_DEBUG}")
set_target_properties(opengl_game::glfw PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_openglgame_include_dir}"
    INTERFACE_LINK_LIBRARIES "OpenGL::GL;user32;gdi32;shell32")

add_library(opengl_game::bullet INTERFACE IMPORTED GLOBAL)
set_target_properties(opengl_game::bullet PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_openglgame_bullet_include_dir}"
    INTERFACE_LINK_LIBRARIES
        "$<$<CONFIG:Debug>:${_openglgame_bullet_collision_DEBUG};${_openglgame_bullet_dynamics_DEBUG};${_openglgame_bullet_softbody_DEBUG};${_openglgame_linear_math_DEBUG}>$<$<NOT:$<CONFIG:Debug>>:${_openglgame_bullet_collision_RELEASE};${_openglgame_bullet_dynamics_RELEASE};${_openglgame_bullet_softbody_RELEASE};${_openglgame_linear_math_RELEASE}>")

_openglgame_make_imported(opengl_game::assimp
    "${_openglgame_assimp_RELEASE}" "${_openglgame_assimp_DEBUG}")
set_target_properties(opengl_game::assimp PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_openglgame_assimp_include_dir}")

function(opengl_game_copy_runtime_dependencies target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -DOPENGLGAME_RUNTIME_DLL_DIR="${_openglgame_config_root}/$<CONFIG>/dll"
            -DOPENGLGAME_RUNTIME_DEST_DIR="$<TARGET_FILE_DIR:${target}>"
            -P "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/CopyRuntimeDependencies.cmake"
        COMMENT "Copying runtime dependency DLLs")
endfunction()

if(OPENGLGAME_ENABLE_FETCHCONTENT)
    message(WARNING
        "OPENGLGAME_ENABLE_FETCHCONTENT is reserved for a future package provider. "
        "This checkout still requires local libraries or an externally configured toolchain.")
endif()
