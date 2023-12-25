#include "Entity.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "MaterialManager.h"
#include <algorithm>
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameCamera.h"


void Entity::setTexture(string&& src)
{
	m_material->setTexture("material.diffuse", src, 0, TextureType::Texture2D);
}

void Entity::setCubeTexture(string&& src)
{
	m_material->setTexture("material.diffuse", src, 0, TextureType::TextureCubMap);
}

weak_ptr<Material> Entity::GetMaterial()
{
	return m_material;
}
Entity::Entity() :
	lightSrc(nullptr),
	m_color(glm::vec3(1.0f, 1.0f, 1.0f)),
	CullFace(GL_BACK),
	m_VAO(-1),
	m_DiffuseMap(-1),
	m_VertexNum(-1)
{
	setNodeType(NodeType::Render);
}


Entity::~Entity()
{
	//for (auto& ref : comList)
	//{
	//	ref->release();
	//}
}
bool Entity::init()
{
	if (!Node::init())
		return false;
	return true;
}

void Entity::draw()
{
	glCullFace(CullFace);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_VertexNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glCullFace(GL_BACK);
}

void Entity::setMeshAndBuffer(std::weak_ptr<Mesh> meshData)
{
	auto mesh = meshData.lock();
	m_VAO = mesh->VAO;
	m_VertexNum = mesh->indices.size();
}

void Entity::setMeshAndBuffer(const Mesh& meshData)
{
	m_VAO = meshData.VAO;
	m_VertexNum = meshData.indices.size();
}

void Entity::setMaterial(const string& materialName)
{
	Material sysMaterial = MaterialManager::getInstance()->getUserMaterial(materialName);
	m_material = std::make_shared<Material>(sysMaterial);
}

void Entity::setColor(glm::vec3 color)
{
	m_color = color;
	m_material->setVec3("mColor", color);
}

glm::vec3 Entity::getColor()
{
	return m_color;
}
