#include "Entity.h"
#include "RenderManager.h"
#include "Shader3D_Component.h"
#include <algorithm>
#include "Component.h"

void Entity::addComponent(Component* component)
{
	component->setEntity(this);
	comList.emplace_back(component);
}
void Entity::setComponent(Component* component)
{
	for (auto p : comList)
	{
		if (p->getComTypeI() == component->getComTypeI())
		{
			p->release();
			component->setEntity(this);
			p = component;
			return;
		}
	}
	addComponent(component);
}
Component* Entity::getComponent(ComponentTypeI typeI)
{
	for (auto& ref : comList)
	{
		if (ref->getComTypeI() == typeI)
			return ref;
	}
	return nullptr;
}

Component* Entity::getComponent(ComponentTypeII typeII)
{
	for (auto& ref : comList)
	{
		if (ref->getComTypeII() == typeII)
			return ref;
	}
	return nullptr;
}
Component* Entity::getComponent(ComponentTypeI typeI, ComponentTypeII typeII)
{
	for (auto& ref : comList)
	{
		if (ref->getComTypeI() == typeI && ref->getComTypeII() == typeII)
			return ref;
	}
	return nullptr;
}

void Entity::setTexture(string&& src)
{
	diffuseMap = RenderManager::getTexture(src);
	for (auto& ref : comList)
	{
		if (ref->getComTypeII() == ComponentTypeII::Shader3D_Tex || ref->getComTypeII() == ComponentTypeII::Shader3D_TexLight)
			static_cast<Shader3D_Component*>(ref)->setTexture(std::move(src));
	}

}
Entity::Entity() : lightSrc(nullptr), color(glm::vec3(1.0f, 1.0f, 1.0f))
{
}


Entity::~Entity()
{
	for (auto& ref : comList)
	{
		ref->release();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
bool Entity::init()
{
	return true;
}
void Entity::draw()
{
	for (auto& sd : comList)
	{
		sd->use();
	}
}
