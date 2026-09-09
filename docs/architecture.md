# OpenGLGame 架构与迁移说明

## 原工程的问题

原项目是一个单一的 Visual Studio Application 工程。源码、资源、第三方头文件、预编译库、Debug/Release 产物和运行时 DLL 混在 `Engine`、`Debug` 和 `Release` 目录中。

主要问题如下：

1. 所有源码都属于一个目标，任何公共头文件变化都会触发大范围重编译。
2. 工程文件和真实源码列表逐渐偏离，构建入口只能依赖手工维护的 `.vcxproj`。
3. include 路径是全局暴露的，头文件经常间接依赖其他头文件，包含顺序影响编译结果。
4. GLAD 和 GLEW 同时出现在工程中：源码调用 GLAD，但工程又链接 GLEW。
5. Debug/Release、x86/x64 的第三方库映射不完整，尤其 x64 缺少 Assimp。
6. 资源路径依赖当前工作目录，并通过宏拼接字符串，不适合从 IDE、脚本或安装目录启动。
7. 管理器、单例、裸指针和手工引用计数互相耦合，初始化和销毁顺序不清晰。
8. 生成的 DLL、可执行文件、IDE 缓存和源码资源重复存在，仓库难以复现。

## 新构建结构

新版由两个 CMake target 组成：

- `opengl_game_engine`：渲染器核心静态库。
- `opengl_game`：创建窗口、初始化 OpenGL 并运行示例场景的程序。

第三方依赖通过 imported/interface target 暴露，不再向所有源码目录注入无关的库搜索路径。项目只保留 GLAD 作为 OpenGL 函数加载器，`glad.c` 由引擎 target 编译一次。

依赖优先顺序为：

1. `OPENGLGAME_DEPS_ROOT` 指定的本地目录。
2. 仓库内 `Engine/external`。
3. 用户显式配置的 vcpkg/FetchContent 等外部依赖提供方。

默认使用本地静态库。共享库模式通过 `OPENGLGAME_USE_SHARED_DEPS=ON` 开启，并把可用 DLL 复制到可执行文件目录。

## 资源策略

构建后，`Engine/Resources` 会被复制到可执行文件旁边的 `Resources` 目录。`ResourceLocator` 优先读取 `OPENGLGAME_RESOURCE_DIR`，否则从可执行文件目录推导资源根目录，最后才回退到当前目录。旧的路径宏目前只是兼容层，内部已经不再保存硬编码的 `Resources/...` 字符串。

## 当前迁移边界

实现文件已经按职责移动到 `src/app`、`src/core`、`src/render`、`src/scene`、`src/physics` 和 `src/input`。为了降低迁移风险，旧头文件暂时仍位于 `Engine` 根目录，并作为兼容 include 层；后续可以在不改变 target 接口的前提下，将公共头文件迁移到 `include/opengl_game`，同时逐步收紧模块之间的可见依赖。
