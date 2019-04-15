#include "Node.h"
#include <list>
#include <glm/gtc/quaternion.hpp>

mat4 Node::getModelMatrix()
{
	mat4 model = mat4(1.0f);
	if (parent)
	{
		model = glm::scale(model, transform.scale);									//Ëõ·Å
		glm::qua<float> q = glm::qua<float>(glm::radians(transform.rotate));		//Ðý×ª
		model = glm::translate(model, parent->getPosition() + transform.position);		//Î»ÒÆ
		
	}
	return model;
}

Node::Node() : parent(nullptr)
{
}


Node::~Node()
{
	for (auto ptr : childs)
		delete ptr;
}

void Node::addChild(Node * node)
{
	childs.push_back(node);
	node->parent = this;
	node->retain();
}

void Node::setPosition(vec3 position)
{
	if (!parent)
		transform.position = position;
	transform.position = position - parent->getPosition();
}

void Node::setLocalPosition(vec3 position)
{
	transform.position = position;
}

void Node::setRotate(vec3 rotate)
{
	transform.rotate = rotate;
}

void Node::setScale(vec3 scale)
{
	transform.scale = scale;
}

vec3 Node::getPosition()
{
	if (!parent)
		return transform.position;

	return parent->getPosition() + transform.position;
}

vec3 Node::getLocalPosition()
{
	return transform.position;
}

vec3 Node::getRotate()
{
	return transform.rotate;
}

vec3 Node::getScale()
{
	return transform.scale;
}

bool Node::init()
{
	return true;
}

void Node::draw()
{
}
