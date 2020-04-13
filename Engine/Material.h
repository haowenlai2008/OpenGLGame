#pragma once
#include "func.h"
class Material
{
public:
	Material();
	Material(vec3& specular, float shininess);
	Material(vec3&& specular, float shininess);
	LL_SYNTHESIZE(vec3, m_specular, Specular);
	LL_SYNTHESIZE(float, m_shininess, Shininess);
};

