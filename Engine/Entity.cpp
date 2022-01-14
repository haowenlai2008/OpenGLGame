#include "Entity.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Shader3D_Component.h"
#include <algorithm>
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameCamera.h"
vec3 EntityColor::Red = vec3(1.0f, 0.0f, 0.0f);
vec3 EntityColor::Orange = vec3(1.0f, 0.65f, 0.0f);
vec3 EntityColor::Yellow = vec3(1.0f, 1.0f, 0.0f);
vec3 EntityColor::Green = vec3(0.0f, 1.0f, 0.0f);
vec3 EntityColor::Cyan = vec3(0.0f, 1.0f, 1.0f);
vec3 EntityColor::Blue = vec3(0.0f, 0.0f, 1.0f);
vec3 EntityColor::Purple = vec3(0.5f, 0.0f, 0.5f);
vec3 EntityColor::Grey = vec3(0.2f, 0.2f, 0.2f);
vec3 EntityColor::Pink = vec3(1.0f, 0.41f, 0.71f);
vec3 EntityColor::Black = vec3(0.0f, 0.0f, 0.0f);


std::unordered_map<MaterialType, std::string> Entity::shaderTypeMap = {
	{MaterialType::TextureCube, "PBRCube"},
	{MaterialType::WithColor, "WithColor"},
	{MaterialType::WithColorAndLight, "WithColorAndLight"},
	{MaterialType::WithTex, "WithTex"},
	{MaterialType::PBR, "PBR"},
};

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

	//auto withTexFun = [&]() {
	//	std::shared_ptr<Shader> shader(m_Shader);
	//	shader->use();
	//	shader->setInt("material.diffuse", 0);

	//	if (m_DiffuseMap != -1)
	//	{
	//		glActiveTexture(GL_TEXTURE0);
	//		glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
	//	}
	//};

	//auto PBRFun = [&]() {
	//	std::shared_ptr<Shader> shader(m_Shader);
	//	shader->use();
	//	if (getLightSrc() != nullptr)
	//		shader->setVec3("light.position", getLightSrc()->getPosition());
	//	shader->setVec3("viewPos", BaseManager::getInstance()->getCamera()->getPosition());
	//	shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	//	shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	//	shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	//	// material properties
	//	shader->setVec3("material.specular", vec3(0.5f, 0.5f, 0.5f));
	//	shader->setFloat("material.shininess", 64.0f);

	//	shader->setInt("material.diffuse", 0);
	//	shader->setInt("shadowMap", 1);

	//	if (m_DiffuseMap != -1)
	//	{
	//		glActiveTexture(GL_TEXTURE0);
	//		glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
	//	}

	//	GLuint shadowMap = RenderManager::getInstance()->getDepthMap();
	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, shadowMap);
	//};

	//auto withColorFunc = [&]() {
	//	std::shared_ptr<Shader> shader(m_Shader);
	//	shader->use();
	//	shader->setVec3("mColor", m_color);
	//};

	//auto withColorAndLightFunc = [&]() {
	//	std::shared_ptr<Shader> shader(m_Shader);
	//	shader->use();
	//	if (getLightSrc() != nullptr)
	//		shader->setVec3("light.position", getLightSrc()->getPosition());
	//	shader->setVec3("viewPos", BaseManager::getInstance()->getCamera()->getPosition());
	//	shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	//	shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	//	shader->setVec3("light.specular", 2.0f, 2.0f, 2.0f);
	//	// material properties
	//	shader->setVec3("material.specular", vec3(0.5f, 0.5f, 0.5f));
	//	shader->setFloat("material.shininess", 64.0f);
	//	shader->setVec3("mColor", m_color);
	//	shader->setInt("shadowMap", 1);

	//	GLuint shadowMap = RenderManager::getInstance()->getDepthMap();
	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, shadowMap);
	//};
	//auto withCubeFunc = [&]() {
	//	std::shared_ptr<Shader> shader(m_Shader);
	//	shader->use();
	//	if (getLightSrc() != nullptr)
	//		shader->setVec3("light.position", getLightSrc()->getPosition());
	//	shader->setVec3("viewPos", BaseManager::getInstance()->getCamera()->getPosition());
	//	shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	//	shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	//	shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	//	// material properties
	//	shader->setVec3("material.specular", vec3(0.5f, 0.5f, 0.5f));
	//	shader->setFloat("material.shininess", 64.0f);

	//	shader->setInt("material.diffuse", 0);
	//	shader->setInt("shadowMap", 1);

	//	if (m_DiffuseMap != -1)
	//	{
	//		glActiveTexture(GL_TEXTURE0);
	//		glBindTexture(GL_TEXTURE_CUBE_MAP, m_DiffuseMap);
	//	}

	//	GLuint shadowMap = RenderManager::getInstance()->getDepthMap();
	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, shadowMap);
	//};
	//switch (m_type)
	//{
	//case MaterialType::WithColor:
	//	withColorFunc();
	//	break;
	//case MaterialType::WithColorAndLight:
	//	withColorAndLightFunc();
	//	break;
	//case MaterialType::WithTex:
	//	withTexFun();
	//	break;
	//case MaterialType::PBR:
	//	PBRFun();
	//	break;
	//case MaterialType::TextureCube:
	//	withCubeFunc();
	//	break;
	//default:
	//	break;
	//}
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
	//m_Shader = Shader::getShader();
	m_material = std::make_shared<Material>(m_type);	//创建材质
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
