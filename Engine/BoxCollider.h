#pragma once
#include "func.h"
class BoxCollider
{
public:
	BoxCollider();
	BoxCollider(float length, float width, float height);
	static BoxCollider Normal();
	LL_SYNTHESIZE(float, m_length, Length);
	LL_SYNTHESIZE(float, m_width, Width);
	LL_SYNTHESIZE(float, m_height, Height);
};

