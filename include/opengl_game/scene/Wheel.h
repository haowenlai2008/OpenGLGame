#pragma once
#include "opengl_game/scene/Node.h"
class Wheel : public Node
{
public:
	CREATE_FUNC(Wheel);
	virtual bool init() override;
	void setRadius(float radius);
	float getRadius();
	float m_Radius;

};

