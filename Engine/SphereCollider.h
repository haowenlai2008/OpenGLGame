#pragma once
#include "func.h"
class SphereCollider
{
public:
	SphereCollider();
	SphereCollider(float radius);
	static SphereCollider Normal();
	LL_SYNTHESIZE(float, m_radius, Raius);
};

