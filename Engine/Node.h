#pragma once
#include <list>
#include "func.h"
#include "Transform.h"
#include "Ref.h"
#include "Component.h"


using std::list;
class Node : public Ref
{
public:
	Node* parent;
	list<Node*> childs;
	Transform transform;
	CREATE_FUNC(Node);
	LL_SYNTHESIZE(bool, isVis, Visable);
	void addChild(Node* node);
	void setPosition(const vec3& position);
	void setPosition(vec3&& position);
	void setLocalPosition(const vec3& position);
	void setLocalPosition(vec3&& position);
	void setRotate(const vec3& rotate);
	void setRotate(vec3&& rotate);
	void setScale(const vec3& scale);
	void setScale(vec3&& scale);
	void Rotate(vec3 rotate);
	vec3 getPosition();
	vec3 getLocalPosition();
	vec3 getRotate();
	vec3 getScale();
	vec3 getLookVector();
	virtual bool init();
	virtual void draw();
	virtual void update(float delta);
	virtual void lateUpdate(float delta);
	virtual void renderParamUpdate();
	mat4 getModelMatrix();
	mat4 getRotateMatrix();
	Node();
	virtual ~Node();

	
};
