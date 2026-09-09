#pragma once
#include "Node.h"
#include "Material.h"
#include "VertexFactory.h"
#include <unordered_map>
class Shader;
class Mesh;
class Material;
using std::weak_ptr;
using std::shared_ptr;

// 实体创建静态函数的宏
#define ENTITY_CREATE_FUNC(__TYPE__) \
static __TYPE__* create(string matType) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
	pRet->setMaterial(matType); \
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
	LL_SYNTHESIZE(Node*, lightSrc, LightSrc);//光源设置
	LL_SYNTHESIZE(GLuint, CullFace, CullFace);		// 设置裁剪方式
	virtual bool init() override;
	virtual void draw() override;
	void setMeshAndBuffer(std::weak_ptr<Mesh> meshData);
	void setMeshAndBuffer(const Mesh& meshData);
	void setMaterial(const string& materialName);
	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	virtual void setTexture(string&& src);
	virtual void setCubeTexture(string&& src);
	weak_ptr<Material> GetMaterial();
	Entity();
	virtual ~Entity();
protected:
	glm::vec3 m_color;
	//vector<Component*> comList;
	shared_ptr<Material> m_material;
	GLuint m_VAO;
	GLuint m_DiffuseMap;
	GLuint m_VertexNum;
};
