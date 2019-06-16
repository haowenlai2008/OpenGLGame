#include "Node.h"
#include <list>
#include <glm/gtc/quaternion.hpp>

mat4 Node::getModelMatrix()
{
	mat4 model = mat4(1.0f);
	if (parent)
	{
		
		model = glm::scale(model, transform.scale);									//����
		vec3 scaleC(1.0f / transform.scale.x, 1.0f / transform.scale.y, 1.0f / transform.scale.z);	//����ϵ��ÿ�������ĵ�����ɵ�����
		vec3 move = parent->getPosition() + transform.position;//�����ϵ�λ��
		model = glm::translate(model, vec3(move.x * scaleC.x, move.y * scaleC.y, move.z * scaleC.z));		//λ��, Ϊ�˱��ֳ߶Ȳ��䣬ȥ�����ŵ�Ӱ��

		glm::qua<float> q = glm::qua<float>(glm::radians(parent->getRotate() + transform.rotate));		//��ת
		model = glm::mat4_cast(q) * model;
	}
	return model;
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
	if (node->parent == nullptr)
	{
		childs.push_back(node);
		node->parent = this;
		node->retain();
	}
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

void Node::Rotate(vec3 rotate)
{
	transform.rotate += rotate;
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
	if (!parent)
		return transform.rotate;
	return parent->getRotate() + transform.rotate;
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

void Node::update(float delta)
{

}