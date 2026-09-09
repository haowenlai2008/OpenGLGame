#pragma once
#include "opengl_game/scene/Node.h"
#include "opengl_game/scene/BSpline.h"
class BSpline;
class Line2D_BSpline : public Node
{
public:
	CREATE_FUNC(Line2D_BSpline);
	std::unique_ptr<BSpline> bSpline;
	virtual bool init() override;
};

