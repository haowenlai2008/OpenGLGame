#pragma once
#include "Node.h"
class Line2D_ColorBalance : public Node
{
public:
	CREATE_FUNC(Line2D_ColorBalance);
	static glm::vec3 transfer(float value);
	virtual bool init() override;
};

