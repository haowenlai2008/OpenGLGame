#include "Entity.h"

void Entity::setLightSrc(Node * node)
{
	lightSrc = node;
}

void Entity::setTexture(std::string src)
{
	LoadTexture(diffuseMap, src);
}

Entity::Entity() : lightSrc(nullptr)
{
}

Entity::~Entity()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
