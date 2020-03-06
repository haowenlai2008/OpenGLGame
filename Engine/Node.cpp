#include "Node.h"
#include <list>
#include <glm/gtc/quaternion.hpp>

mat4 Node::getModelMatrix()
{
	mat4 model = mat4(1.0f);
	mat4 trans = glm::translate(model, transform.position);		//位移
	mat4 scale = glm::scale(model, transform.scale);									//缩放
	
	glm::qua<float> q = glm::qua<float>(glm::radians(transform.rotate));		//旋转
	mat4 rotate = glm::mat4_cast(q);
	model = trans * scale * rotate;
	if (parent)
		return parent->getModelMatrix() * model;
	else
		return model;
}

mat4 Node::getRotateMatrix()
{
	mat4 model = mat4(1.0f);
	glm::qua<float> q = glm::qua<float>(glm::radians(transform.rotate));		//旋转
	mat4 rotate = glm::mat4_cast(q);
	if (parent)
		return parent->getRotateMatrix() * rotate;
	else
		return rotate;
}

Node::Node() : parent(nullptr), isVis(true)
{
}


Node::~Node()
{
	for (auto ptr : childs)
		ptr->release();
}

void Node::addChild(Node * node)
{
	for (auto*& p : node->childs)
	{
		if (p == nullptr)
		{
			p = node;
			p->retain();
			return;
		}
	}
	if (node->parent == nullptr)
	{
		childs.push_back(node);
		node->parent = this;
		node->retain();
	}
}

void Node::setPosition(const vec3& position)
{
	if (parent)
		transform.position = position - parent->getPosition();
	else
		transform.position = position;
}

void Node::setPosition(vec3&& position)
{
	if (parent)
		transform.position = position - parent->getPosition();
	else
		transform.position = position;
}

void Node::setLocalPosition(const vec3& position)
{
	transform.position = position;
}

void Node::setLocalPosition(vec3&& position)
{
	transform.position = position;
}

void Node::setRotate(const vec3& rotate)
{
	transform.rotate = rotate;
}

void Node::setRotate(vec3&& rotate)
{
	transform.rotate = rotate;
}

void Node::setScale(const vec3& scale)
{
	transform.scale = scale;
}

void Node::setScale(vec3&& scale)
{
	transform.scale = scale;
}


void Node::Rotate(vec3 rotate)
{
	transform.rotate += rotate;
}

vec3 Node::getPosition()
{
	Node* m_parent = parent;
	vec3 pos = transform.position;
	while (m_parent)
	{
		pos += m_parent->getLocalPosition();
		m_parent = m_parent->parent;
	};
	return pos;
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

vec3 Node::getLookVector()
{
	return  vec3(getRotateMatrix() * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
}

bool Node::init()
{
	return true;
}

void Node::draw()
{
}

void Node::update(float delta)
{

}

void Node::lateUpdate(float delta)
{
}

void Node::renderParamUpdate()
{
}
