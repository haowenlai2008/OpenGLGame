#pragma once
#include "Node.h"

class Scene : public Node
{
public:
	CREATE_FUNC(Scene);
	virtual bool init();
};
