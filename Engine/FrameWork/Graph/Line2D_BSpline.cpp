#include "Line2D_BSpline.h"
#include "allShaderComponent.h"
#include "Line2D.h"
#include "BSpline.h"
bool Line2D_BSpline::init()
{
	Line2D* line1 = Line2D::create();
	bSpline = std::make_unique<BSpline>();
	bSpline->addOriginPoints(glm::vec2(0.0f, 0.0f));
	bSpline->addOriginPoints(glm::vec2(255.0f, 255.0f));
	bSpline->update();
	for (int i = 0; i < bSpline->colorMap.size(); i++)
	{
		float x = (float)i / bSpline->colorMap.size();
		float y = (float)bSpline->colorMap[i] / (float)bSpline->colorMap.size();
		glm::vec2 realPos(x * 2 - 1, y * 2 - 1);
		line1->addPoint(realPos);
	}
	this->addChild(line1);
	return true;
}
