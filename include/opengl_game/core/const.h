#pragma once

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include "opengl_game/core/ResourceLocator.h"

using std::string;
using std::vector;
using glm::vec3;

#define ERROR_TEX_ID -1
#define TEXTURE_PATH (ResourceLocator::directory("Texture"))
#define SHADER_PATH (ResourceLocator::directory("Shader"))
#define MODEL_PATH (ResourceLocator::directory("Model"))
#define DOT_MAT_PATH (ResourceLocator::directory("DotMatrix"))
#define FILTER_PATH (ResourceLocator::directory("Shader/Filter"))
#define MATERIAL_PATH (ResourceLocator::directory("Material"))
#define FILTER_VS (ResourceLocator::file("Shader/Filter/filterBase.vs"))
#define SKY_BOX (std::string("sor_cwd"))

namespace Const
{
    inline vector<string> facesName =
    {
        "/right.jpg",
        "/left.jpg",
        "/top.jpg",
        "/bottom.jpg",
        "/front.jpg",
        "/back.jpg"
    };

    class EntityColor
    {
    public:
        static vec3 Red;
        static vec3 Orange;
        static vec3 Yellow;
        static vec3 Green;
        static vec3 Cyan;
        static vec3 Blue;
        static vec3 Purple;
        static vec3 Grey;
        static vec3 Pink;
        static vec3 Black;
    };
}