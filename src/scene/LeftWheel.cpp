#include "LeftWheel.h"
#include "CylinderNoCap.h"
#include "Circle.h"
#include "Cube.h"
bool LeftWheel::init()
{
	CylinderNoCap* cnc = CylinderNoCap::create("PBR");
	this->addChild(cnc);
	cnc->setTexture("wheel.jpg");
	cnc->setLocalPosition(vec3(-0.25f, 0.0f, 0.0f));
	cnc->setScale(vec3(0.5f, 1.0f, 1.0f));

	Circle* c1 = Circle::create("PBR");
	this->addChild(c1);
	c1->setTexture("wheelface.jpg");
	c1->setLocalPosition(vec3(0.0f, 0.0f, 0.0f));

	Circle* c2 = Circle::create("PBR");
	this->addChild(c2);
	c2->setTexture("wheelface.jpg");
	c2->setLocalPosition(vec3(-0.5f, 0.0f, 0.0f));
	c2->setRotate(vec3(0.0f, 180.0f, 0.0f));//翻转180度

	setRadius(0.5f);
	return true;
}
