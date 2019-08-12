#pragma once
#include "Entity.h"
class Line2D : public Entity
{
public:
	CREATE_FUNC(Line2D);
	vector<float> points;
	void addPoint(glm::vec2 point);
	void clear();
	void setColor(glm::vec3 color);
	virtual bool init() override;
	virtual void draw() override;
	virtual void update(float delta) override;
};

