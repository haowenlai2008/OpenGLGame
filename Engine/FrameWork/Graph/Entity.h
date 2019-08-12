#pragma once
#include "Node.h"
class Shader;
class Component;
class Entity : public Node
{
public:
	CREATE_FUNC(Entity);
	LL_SYNTHESIZE(glm::vec3, color, Color);//��ɫ����
	LL_SYNTHESIZE(Node*, lightSrc, LightSrc);//��Դ����
	virtual bool init() override;
	virtual void draw() override;
	virtual void setTexture(string&& src);
	void addComponent(Component* component);
	void setComponent(Component* component);
	Component* getComponent(ComponentTypeI typeI);	//���ݴ��������
	Component* getComponent(ComponentTypeII typeII);//����С�������
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
