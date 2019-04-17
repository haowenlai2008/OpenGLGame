#pragma once
#include "Node.h"

class Entity : public Node
{
public:
	CREATE_FUNC(Entity);
	LL_SYNTHESIZE(glm::vec3, color, Color);
	virtual void setLightSrc(Node* node);
	void setTexture(std::string src);
	Entity();
	virtual ~Entity();
protected:
	Node* lightSrc;
	Shader shader;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int diffuseMap;
};
