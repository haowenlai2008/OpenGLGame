if(NOT DEFINED OPENGLGAME_RUNTIME_DLL_DIR OR
   NOT DEFINED OPENGLGAME_RUNTIME_DEST_DIR)
    message(FATAL_ERROR "Runtime dependency copy paths were not provided")
endif()

foreach(_name IN ITEMS glfw3.dll glew32.dll glew32d.dll assimp-vc140-mt.dll)
    set(_source "${OPENGLGAME_RUNTIME_DLL_DIR}/${_name}")
    if(EXISTS "${_source}")
        file(COPY "${_source}" DESTINATION "${OPENGLGAME_RUNTIME_DEST_DIR}")
    endif()
endforeach()
