#pragma once
#include "Node.h"
#include "Shader.h"
#include "Component.h"
class Entity : public Node
{
public:
	CREATE_FUNC(Entity);
	LL_SYNTHESIZE(glm::vec3, color, Color);//��ɫ����
	LL_SYNTHESIZE(Node*, lightSrc, LightSrc);//��Դ����
	virtual void draw();
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
	Shader shader;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int diffuseMap;
};
