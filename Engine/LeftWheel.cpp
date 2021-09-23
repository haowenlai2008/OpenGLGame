#include "LeftWheel.h"
#include "CylinderNoCap.h"
#include "Circle.h"
bool LeftWheel::init()
{
	CylinderNoCap* cnc = CylinderNoCap::create(Entity_Type::WithTexAndLight);
	cnc->setTexture("wheel.jpg");
	cnc->setLocalPosition(vec3(-0.25f, 0.0f, 0.0f));
	cnc->setScale(vec3(0.5f, 1.0f, 1.0f));
	this->addChild(cnc);

	Circle* c1 = Circle::create(Entity_Type::WithTexAndLight);
	c1->setTexture("wheelface.jpg");
	c1->setLocalPosition(vec3(0.0f, 0.0f, 0.0f));
	this->addChild(c1);

	Circle* c2 = Circle::create(Entity_Type::WithTexAndLight);
	c2->setTexture("wheelface.jpg");
	c2->setLocalPosition(vec3(-0.5f, 0.0f, 0.0f));
	c2->setRotate(vec3(0.0f, 180.0f, 0.0f));//翻转180度
	this->addChild(c2);

	setRadius(1.0f);
	return true;
}
