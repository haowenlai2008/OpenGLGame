# Refactor Migration Log

This document records the completed refactor stages and the remaining work.

## Completed stages

1. `8fec89b` - migrated the Visual Studio-only project to CMake. Added local
   dependency discovery, architecture presets, runtime DLL copying, resource
   location, and a CTest resource-path test.
2. `58d6a9a` - moved implementation files into `src/app`, `src/core`,
   `src/input`, `src/physics`, `src/render`, and `src/scene`.
3. `f5339ab` - moved public headers into `include/opengl_game/<module>` and
   placed the vendored nlohmann JSON header under the third-party include root.
4. `290bbdf` - qualified project includes with `opengl_game/...` paths and
   removed the module-directory compatibility include paths from CMake.
5. `3f16d03` - fixed an invalid include directive and made MSVC's legacy CRT
   warning policy explicit for the existing `getenv` usage.
6. `2406c8f` - added a public-header compile smoke target that includes the
   complete API surface independently of the renderer implementation.

Every stage was built with the local Win32 dependency set. Debug builds and
CTest pass; Release builds also link successfully. The x64 preset intentionally
fails early when the repository does not contain an x64 Assimp build.

## Why the old design was costly

- Source, headers, generated objects, DLLs, and resources shared one directory.
- The `.vcxproj` was the source-of-truth for the file list and build settings.
- Flat include paths made dependencies implicit and caused broad rebuilds.
- GLAD and GLEW appeared together even though only GLAD was used.
- Relative resource macros depended on the process working directory.
- Manual retain/release and raw Bullet allocations obscure ownership and teardown.
- Debug/Release and x86/x64 library selection was not validated by the build.

## Current design

- CMake owns targets, configuration, architecture selection, and installation.
- `opengl_game_engine` is a static library; `opengl_game` is the executable.
- Local static libraries are preferred. Shared libraries, when selected, have
  their actual runtime DLLs copied beside the executable.
- `ResourceLocator` resolves an environment override first, then the executable
  directory, so launching from an IDE or another working directory is stable.
- GLAD is the only OpenGL loader compiled into the project.
- Public headers have stable namespaced paths and are checked by a compile-only
  smoke target.

## Remaining technical debt

The runtime still contains legacy ownership patterns in scene and Bullet code,
some broad headers, and existing numeric-conversion warnings. These should be
addressed incrementally with RAII wrappers and narrower interfaces; changing
them was deliberately kept separate from the build/layout migration so each
commit remains easy to validate.

## x64 dependency status

The repository now includes x64 GLFW and Assimp import libraries plus their
runtime DLLs under `Engine/external/x64`. The x64 Assimp build is generated from
the locally downloaded Assimp 5.4.3 source; that source tree and intermediate
build directories are ignored, while the tested binaries are kept with the
project dependencies. The x64 preset can therefore be configured directly:

```powershell
cmake --preset x64-local
cmake --build --preset x64-debug
```
