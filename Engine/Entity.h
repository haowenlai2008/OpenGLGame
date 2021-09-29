#pragma once
#include "Node.h"
#include "VertexFactory.h"
class Shader;
class Component;
class Mesh;
class Material;
using std::weak_ptr;
using std::shared_ptr;
enum class Entity_Type
{
	WithColor,
	WithColorAndLight,
	WithTex,
	WithTexAndLight,
	TextureCube, //
};

class EntityColor
{
public:
	static vec3 Red;
	static vec3 Orange;
	static vec3 Yellow;
	static vec3 Green;
	static vec3 Cyan;
	static vec3 Blue;
	static vec3 Purple;
	static vec3 Grey;
	static vec3 Pink;
	static vec3 Black;
};
// 实体创建静态函数的宏
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
	LL_SYNTHESIZE(glm::vec3, m_color, Color);//颜色设置
	LL_SYNTHESIZE(Node*, lightSrc, LightSrc);//光源设置
	LL_SYNTHESIZE_READ(Entity_Type, m_type, EntityType);
	virtual bool init() override;
	virtual void draw() override;
	virtual void renderParamUpdate();
	void setMeshAndBuffer(std::weak_ptr<Mesh> meshData);
	void setMaterial(vec3& specular, float shininess);
	void setMaterial(vec3&& specular, float shininess);
	virtual void setTexture(string&& src);
	virtual void setCubeTexture(string&& src);
	virtual void bindShaderResource();
	
	Entity();
	virtual ~Entity();
protected:
	vector<Component*> comList;
	weak_ptr<Shader> m_Shader;
	shared_ptr<Material> m_material;
	vector<shared_ptr<Mesh>> m_meshList;
	vector<shared_ptr<Material>> m_materialList;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_DiffuseMap;
	GLuint m_ShadowMap;
	GLuint m_VertexNum;
};
