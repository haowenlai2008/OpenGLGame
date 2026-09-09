# 构建说明

## 要求

- Windows 10/11
- Visual Studio 2019 或更新版本
- CMake 3.20 或更新版本
- 与目标架构匹配的本地第三方库

## x64 构建

```powershell
cmake -S . -B build -A x64
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

也可以使用 Win32 预设：

```powershell
cmake --preset win32-local
cmake --build --preset win32-debug
ctest --preset win32-debug-tests
```

x64 预设：

```powershell
cmake --preset x64-local
cmake --build --preset x64-debug
```

当前仓库的本地预编译 Assimp 主要位于 x86 目录。如果 x64 配置报告缺少 `assimp-vc140-mt`，请通过 `OPENGLGAME_DEPS_ROOT` 指向匹配的 x64 依赖，或接入 vcpkg/FetchContent 提供 Assimp。

## x86 构建

```powershell
cmake -S . -B build-x86 -A Win32
cmake --build build-x86 --config Debug
```

## 本地依赖位置

```text
Engine/external/include
Engine/external/source/bullet
Engine/external/x86/{Debug,Release}/{lib,dll}
Engine/external/x64/{Debug,Release}/{lib,dll}
```

可以覆盖依赖根目录：

```powershell
cmake -S . -B build -A x64 `
  -DOPENGLGAME_DEPS_ROOT=C:/third_party/openglgame
```

共享库/导入库模式（使用本地导入库，并在运行时复制仓库中实际存在的 DLL）：

```powershell
cmake -S . -B build-shared -A x64 `
  -DOPENGLGAME_USE_SHARED_DEPS=ON
```

`OPENGLGAME_ENABLE_FETCHCONTENT` 目前只保留为扩展点并会给出提示；若使用 vcpkg，请通过 CMake toolchain file 提供匹配架构的 GLFW、Assimp 和 Bullet，仍然由 `OPENGLGAME_DEPS_ROOT` 优先使用仓库内依赖。

仓库里的 Bullet/GLFW `.lib` 主要是静态库；本地 Assimp 的 `.lib` 与 DLL 是否为导入库取决于所提供的二进制包。CMake 会严格按架构和配置选择库，不能把 x86 库链接到 x64 目标。

程序和资源输出在：

```text
build/bin/<配置>/opengl_game.exe
build/bin/<配置>/Resources
```

如需从其他位置加载资源，可以设置：

```powershell
$env:OPENGLGAME_RESOURCE_DIR = "D:/OpenGLGameResources"
```
