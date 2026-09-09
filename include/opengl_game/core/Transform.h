#pragma once
#include "opengl_game/core/func.h"

class Transform
{
public:
	vec3 position;
	vec3 rotate;
	vec3 scale;
	Transform();
	~Transform();
};
