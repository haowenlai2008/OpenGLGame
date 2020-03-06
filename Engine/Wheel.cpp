#include "Wheel.h"
#include "CylinderNoCap.h"
#include "Circle.h"
bool Wheel::init()
{
	CylinderNoCap* cnc = CylinderNoCap::create(Entity_Type::WithTex);
	cnc->setTexture("wheel.jpg");
	cnc->setScale(vec3(0.5f, 1.0f, 1.0f));
	this->addChild(cnc);

	Circle* c1 = Circle::create(Entity_Type::WithTex);
	c1->setTexture("wheelface.jpg");
	c1->setPosition(vec3(0.25f, 0.0f, 0.0f));
	this->addChild(c1);

	Circle* c2 = Circle::create(Entity_Type::WithTex);
	c2->setTexture("wheelface.jpg");
	c2->setPosition(vec3(-0.25f, 0.0f, 0.0f));
	c2->setRotate(vec3(0.0f, 180.0f, 0.0f));//翻转180度
	this->addChild(c2);

	setRadius(0.5f);
	return true;
}

void Wheel::setRadius(float radius)
{
	m_Radius = radius;
	setScale(vec3(1.0f, m_Radius, m_Radius));
}

float Wheel::getRadius()
{
	return m_Radius;
}
