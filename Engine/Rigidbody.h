#pragma once
#include "func.h"
class Rigidbody
{
public:
	Rigidbody();
	Rigidbody(float mass, float frict);
	LL_SYNTHESIZE(float, m_mass, Mass);
	LL_SYNTHESIZE(float, m_frict, Frict);
};

