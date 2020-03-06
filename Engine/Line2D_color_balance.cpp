#include "Line2D_color_balance.h"
#include "allShaderComponent.h"
#include "Line2D.h"
glm::vec3 Line2D_ColorBalance::transfer(float value)
{
	const float a = 64.0f, b = 85.0f, scale = 1.785f;
	glm::vec3 result;
	float i = value * 255.0f;
	float shadows = glm::clamp((i - b) / -a + 0.5f, 0.0f, 1.0f) * scale;
	float midtones = glm::clamp((i - b) / a + 0.5f, 0.0f, 1.0f) * glm::clamp((i + b - 255.0f) / -a + 0.5f, 0.0f, 1.0f) * scale;
	float highlights = glm::clamp(((255.0f - i) - b) / -a + 0.5f, 0.0f, 1.0f) * scale;
	result.r = shadows;
	result.g = midtones;
	result.b = highlights;
	return result;
}

bool Line2D_ColorBalance::init()
{
	Line2D* line1 = Line2D::create();
	Line2D* line2 = Line2D::create();
	Line2D* line3 = Line2D::create();
	for (int i = 0; i < 256; i++)
	{
		float value = (float)i / 255.0f;
		glm::vec3 weight = (transfer(value) / 1.785f) * 1.8f - 0.9f;
		float x = value * 1.8f - 0.9f;
		line1->addPoint(glm::vec2(x, weight.r));
		line2->addPoint(glm::vec2(x, weight.g));
		line3->addPoint(glm::vec2(x, weight.b));
	}
	line1->setColor(glm::vec3(1.0, 0.0, 0.0));
	line2->setColor(glm::vec3(0.0, 1.0, 0.0));
	line3->setColor(glm::vec3(0.0, 0.0, 1.0));
	this->addChild(line1);
	this->addChild(line2);
	this->addChild(line3);
	return true;
}
