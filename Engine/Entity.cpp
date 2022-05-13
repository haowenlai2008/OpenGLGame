#include "Entity.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "MaterialManager.h"
#include "Shader3D_Component.h"
#include <algorithm>
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameCamera.h"


void Entity::setTexture(string&& src)
{
	m_DiffuseMap = RenderManager::getTexture(src);
	m_material->setTextureCacheID("material.diffuse", m_DiffuseMap);
}

void Entity::setCubeTexture(string&& src)
{
	m_DiffuseMap = RenderManager::getCubeTexture(src);
	m_material->setTextureCacheID("material.diffuse", m_DiffuseMap);
}

void Entity::bindShaderResource()
{
	if (RenderManager::getInstance()->getIsShadow())
		return;

}
weak_ptr<Material> Entity::GetMaterial()
{
	return m_material;
}
Entity::Entity() :
	lightSrc(nullptr),
	m_color(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_type(MaterialType::WithColor),
	m_VAO(-1),
	m_VBO(-1),
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
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}
bool Entity::init()
{
	if (!Node::init())
		return false;
	//m_Shader = Shader::getShader();
	auto& sysMaterial = MaterialManager::getInstance()->getSystemMaterial(m_type);
	m_material = std::make_shared<Material>(sysMaterial);
	return true;
}
void Entity::draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_VertexNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Entity::renderParamUpdate()
{
	//if (m_Shader.expired())
	//	return;
	//auto rm = RenderManager::getInstance();
	//std::shared_ptr<Shader> shader;
	//if (rm->getIsShadow())
	//{
	//	shader = rm->getSimpleDepthShader();
	//}
	//else
	//{
	//	shader = m_Shader.lock();
	//}
	//BaseManager* baseManager = BaseManager::getInstance();
	//glm::mat4 projection = baseManager->getProjMat4();
	//glm::mat4 view = baseManager->getViewMat4();
	//glm::mat4 model = getModelMatrix();
	//glm::mat4 lightSpace = baseManager->getLightSpaceMat4();
	//
	//shader->use();
	//shader->setMat4("projection", projection);
	//shader->setMat4("view", view);
	//shader->setMat4("model", model);
	//shader->setMat4("lightSpaceMatrix", lightSpace);
	//bindShaderResource();

}

void Entity::setMeshAndBuffer(std::weak_ptr<Mesh> meshData)
{
	auto mesh = meshData.lock();
	if (m_VAO != -1)
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	if (m_VBO != -1)
	{
		glDeleteBuffers(1, &m_VBO);
	}
	if (m_EBO != -1)
	{
		glDeleteBuffers(1, &m_EBO);
	}
	m_VertexNum = mesh->indices.size();
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);// 绑定顶点数组对象
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//绑定顶点缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertexData.size(), mesh->vertexData.begin()._Ptr, GL_STATIC_DRAW);
	//坐标
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glEnableVertexAttribArray(0);
	//法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//绑定索引缓存
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(GLuint), mesh->indices.begin()._Ptr, GL_STATIC_DRAW);
}

void Entity::setMaterial(vec3& specular, float shininess)
{
	m_material->setVec3("material.specular", specular);
	m_material->setFloat("material.shininess", shininess);
}

void Entity::setMaterial(vec3&& specular, float shininess)
{
	m_material->setVec3("material.specular", specular);
	m_material->setFloat("material.shininess", shininess);
}
