#pragma once
#include "Node.h"
class Shader;
class Component;
class Entity : public Node
{
public:
	CREATE_FUNC(Entity);
	LL_SYNTHESIZE(glm::vec3, color, Color);//颜色设置
	LL_SYNTHESIZE(Node*, lightSrc, LightSrc);//光源设置
	virtual bool init() override;
	virtual void draw() override;
	virtual void setTexture(string&& src);
	void addComponent(Component* component);
	void setComponent(Component* component);
	Component* getComponent(ComponentTypeI typeI);	//根据大类获得组件
	Component* getComponent(ComponentTypeII typeII);//根据小类获得组件
	Component* getComponent(ComponentTypeI typeI, ComponentTypeII typeII);
	Entity();
	virtual ~Entity();
protected:
	vector<Component*> comList;
	std::shared_ptr<Shader> shader;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int diffuseMap;
};
