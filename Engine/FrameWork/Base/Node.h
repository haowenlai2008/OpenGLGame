#pragma once
#include "Transform.h"
#include "Ref.h"
#include "func.h"
#include "Shader/Shader.h"
#include <list>

using std::list;
class Node : public Ref
{
public:
	Node* parent;
	list<Node*> childs;
	Transform transform;
	CREATE_FUNC(Node);
	void addChild(Node* node);
	void setPosition(vec3 position);
	void setLocalPosition(vec3 position);
	void setRotate(vec3 rotate);
	void setScale(vec3 scale);
	vec3 getPosition();
	vec3 getLocalPosition();
	vec3 getRotate();
	vec3 getScale();
	
	virtual bool init();
	virtual void draw();
	mat4 getModelMatrix();
	Node();
	virtual ~Node();

	
};
