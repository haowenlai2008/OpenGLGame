# Current Source Layout

The renderer is now split into conventional source and public-header roots:

```text
src/
  app/       executable entry point
  core/      lifetime, shared data, resource location, base manager
  input/     keyboard and mouse adapters
  physics/   Bullet-backed collision and rigid-body code
  render/    cameras, materials, meshes, shaders, render passes
  scene/     entities, geometry, scenes, and procedural terrain
include/opengl_game/
  core/ input/ physics/ render/ scene/
```

The headers retain their historical short include names for this migration
step. CMake exposes each module include directory as a compatibility layer;
the next cleanup stage will replace those names with `opengl_game/...` paths
and remove the compatibility directories from the public target interface.

The vendored nlohmann JSON header lives under
`Engine/external/include/nlohmann`. `Engine/external/include/json.hpp` is a
small compatibility wrapper for the old include spelling.

`BSpline.cpp` is now part of `src/scene` so it is included by the recursive
source collection and linked into the engine library.
