#pragma once
#include "Node.h"
#include "BSpline.h"
class BSpline;
class Line2D_BSpline : public Node
{
public:
	CREATE_FUNC(Line2D_BSpline);
	std::unique_ptr<BSpline> bSpline;
	virtual bool init() override;
};

