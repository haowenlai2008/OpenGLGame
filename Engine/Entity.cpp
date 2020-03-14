#include "Entity.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Shader3D_Component.h"
#include <algorithm>
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameCamera.h"

void Entity::setTexture(string&& src)
{
	m_DiffuseMap = RenderManager::getTexture(src);


}
void Entity::bindShaderResource()
{
	if (RenderManager::getInstance()->getIsShadow())
		return;
	if (m_type == Entity_Type::WithTex)
	{
		std::shared_ptr<Shader> shader(m_Shader);
		shader->use();
		if (getLightSrc() != nullptr)
			shader->setVec3("light.position", getLightSrc()->getPosition());
		shader->setVec3("viewPos", BaseManager::getInstance()->getCamera()->getPosition());
		shader->setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
		shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		// material properties
		shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader->setFloat("material.shininess", 64.0f);

		shader->setInt("material.diffuse", 0);
		shader->setInt("shadowMap", 1);
		
		if (m_DiffuseMap != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
		}
			
		GLuint shadowMap = RenderManager::getInstance()->getDepthMap();
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shadowMap);


	}

}
Entity::Entity() : 
	lightSrc(nullptr), 
	color(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_type(Entity_Type::WithColor),
	m_VAO(-1),
	m_VBO(-1),
	m_DiffuseMap(-1),
	m_VertexNum(-1)
{
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
	//m_Shader = Shader::getShader();
	string shaderName;
	switch (m_type)
	{
	case Entity_Type::TextureCube:
		shaderName = "cube";
		break;
	case Entity_Type::WithColor:
		shaderName = "color";
		break;
	case Entity_Type::WithTex:
		shaderName = "texture";
		break;
	default:
		break;
	}
	m_Shader = Shader::getShader(shaderName);
	return true;
}
void Entity::draw()
{
	glBindVertexArray(m_VAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glDrawElements(GL_TRIANGLES, m_VertexNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Entity::renderParamUpdate()
{
	if (m_Shader.expired())
		return;
	auto rm = RenderManager::getInstance();
	std::shared_ptr<Shader> shader;
	if (rm->getIsShadow())
	{
		shader = rm->getSimpleDepthShader();
	}
	else
	{
		shader = m_Shader.lock();
	}
	BaseManager* baseManager = BaseManager::getInstance();
	glm::mat4 projection = baseManager->getProjMat4();
	glm::mat4 view = baseManager->getViewMat4();
	glm::mat4 model = getModelMatrix();
	glm::mat4 lightSpace = baseManager->getLightSpaceMat4();
	
	shader->use();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);
	shader->setMat4("lightSpaceMatrix", lightSpace);
	bindShaderResource();

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshData) * mesh->vertexData.size(), mesh->vertexData.begin()._Ptr, GL_STATIC_DRAW);
	//坐标
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData), (void*)(0));
	glEnableVertexAttribArray(0);
	//法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshData), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//绑定索引缓存
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(GLuint), mesh->indices.begin()._Ptr, GL_STATIC_DRAW);
}
