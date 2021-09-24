#include "Node.h"
#include <list>
#include <glm/gtc/quaternion.hpp>
#include "bulletHead.h"
#include "Rigidbody.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"



mat4 Node::getModelMatrix()
{
	mat4 model = mat4(1.0f);
	mat4 trans = glm::translate(model, transform.position);		//位移
	mat4 scale = glm::scale(model, transform.scale);									//缩放
	
	glm::qua<float> q = glm::qua<float>(glm::radians(transform.rotate));		//旋转
	mat4 rotate = glm::mat4_cast(q);
	model = trans * rotate * scale;
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

Node::Node() : parent(nullptr), isVis(true), isPhysicActive(false), m_btrd(nullptr), debugID(0)
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
	vec3 pos;
	if (parent)
	{
		pos = position - parent->getPosition();
	}
	else
	{
		pos = position;
	}
	transform.position = pos;
	//if (m_btrd != nullptr)
	//{
	//	btQuaternion quaternion(transform.rotate.x, transform.rotate.y, transform.rotate.z, 1.0f);
	//	btVector3 pos(transform.position.x, transform.position.y, transform.position.z);
	//	btTransform btt(quaternion, pos);
	//	m_btrd->setWorldTransform(btt);
	//}
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

void Node::physicUpdate(float delta)
{
	if (m_btrd != nullptr)
	{
		btQuaternion quaternion(transform.rotate.x, transform.rotate.y, transform.rotate.z, 1.0f);
		btVector3 pos(transform.position.x, transform.position.y, transform.position.z);
		btTransform btt(quaternion, pos);
		m_btrd->setWorldTransform(btt);
	}
	
}

void Node::lateUpdate(float delta)
{
}

void Node::physicLateUpdate(float delta)
{
	if (m_btrd != nullptr)
	{
		btTransform btt = m_btrd->getWorldTransform();
		btVector3 btVec3 = btt.getOrigin();
		btQuaternion btQt = btt.getRotation();
		setPosition(vec3(btVec3.x(), btVec3.y(), btVec3.z()));
		setRotate(vec3(btQt.x(), btQt.y(), btQt.z()));
	}
}

void Node::renderParamUpdate()
{
}

void Node::addSphereRigidBody()
{
	auto pscm = PhysicsManager::getInstance();
	m_btrd = pscm->addRigidBody(SphereCollider::Normal(), Rigidbody(10.0f, 0.5f));
}

void Node::addSphereRigidBody(float radius)
{
	auto pscm = PhysicsManager::getInstance();
	m_btrd =  pscm->addRigidBody(SphereCollider(radius), Rigidbody(10.0f, 0.5f));
}

void Node::addBoxRigidBody()
{
	auto pscm = PhysicsManager::getInstance();
	m_btrd = pscm->addRigidBody(BoxCollider::Normal(), Rigidbody(10.0f, 0.5f));
}

void Node::addBoxRigidBody(float length, float width, float height)
{
	auto pscm = PhysicsManager::getInstance();
	m_btrd = pscm->addRigidBody(BoxCollider(length, width, height), Rigidbody(10.0f, 0.5f));
}
