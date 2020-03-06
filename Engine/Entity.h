#pragma once
#include "Node.h"
#include "VertexFactory.h"
class Shader;
class Component;
class Mesh;

enum class Entity_Type
{
	WithColor,
	WithTex,
	TextureCube, //
};

// ʵ�崴����̬�����ĺ�
#define ENTITY_CREATE_FUNC(__TYPE__) \
static __TYPE__* create(Entity_Type Etype) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
	pRet->setEntityType(Etype); \
	if (pRet && pRet->init()) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = nullptr; \
	return nullptr; \
	} \
};
class Entity : public Node
{
public:
	CREATE_FUNC(Entity);
	LL_SYNTHESIZE(glm::vec3, color, Color);//��ɫ����
	LL_SYNTHESIZE(Node*, lightSrc, LightSrc);//��Դ����
	LL_SYNTHESIZE_READ(Entity_Type, m_type, EntityType);
	virtual bool init() override;
	virtual void draw() override;
	virtual void renderParamUpdate();
	void setMeshAndBuffer(std::weak_ptr<Mesh> meshData);
	virtual void setTexture(string&& src);
	virtual void bindShaderResource();
	//void addComponent(Component* component);
	//void setComponent(Component* component);
	//Component* getComponent(ComponentTypeI typeI);	//���ݴ��������
	//Component* getComponent(ComponentTypeII typeII);//����С�������
	//Component* getComponent(ComponentTypeI typeI, ComponentTypeII typeII);
	Entity();
	virtual ~Entity();
protected:
	vector<Component*> comList;
	std::weak_ptr<Shader> m_Shader;
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
	unsigned int m_DiffuseMap;
	unsigned int m_VertexNum;
};
