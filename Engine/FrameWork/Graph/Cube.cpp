#include "Cube.h"
#include "BaseManager.h"

vector<float> Cube::vertex  = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
Cube * Cube::create(CubeType _cubeType)
{
	Cube *pRet = new(std::nothrow) Cube();
	pRet->cubeType = _cubeType;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
bool Cube::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);// 绑定顶点数组对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定顶点缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.begin()._Ptr, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));	//最后一个参数是数据的起点
	glEnableVertexAttribArray(0);
	switch (cubeType)
	{
	case CubeType::normal:
		shader = Shader("normal.vs", "normal.fs");
	case CubeType::withLight:
		shader = Shader("withLight.vs", "withLight.fs");
		//法线
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
		glEnableVertexAttribArray(1);
		break;
	case CubeType::withTexture:
		shader = Shader("withTexture.vs", "withTexture.fs");
		//纹理坐标
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//最后一个参数是数据的起点
		glEnableVertexAttribArray(1);
		break;
	case CubeType::withTexAndLight:
		shader = Shader("withTexAndLight.vs", "withTexAndLight.fs");
		shader.setInt("material.diffuse", 0);
		//法线
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
		glEnableVertexAttribArray(1);
		//纹理坐标
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//最后一个参数是数据的起点
		glEnableVertexAttribArray(2);
		break;
	}
	shader.use();
	glBindVertexArray(VAO);
	std::cout << "Cube init" << std::endl;
	return true;
}

void Cube::draw()
{
	glBindVertexArray(VAO);
	BaseManager* baseManager = BaseManager::getInstance();
	Camera& camera = *baseManager->getCamera();
	shader.use();

	switch (cubeType)
	{
	case CubeType::withLight:
		if (lightSrc)
		{
			shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
			shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			shader.setVec3("lightPos", lightSrc->getPosition());
			shader.setVec3("viewPos", camera.Position);
		}
		break;
	case CubeType::withTexture:

		break;
	case CubeType::withTexAndLight:
		if (lightSrc)
		{
			shader.setVec3("light.position", lightSrc->getPosition());
			shader.setVec3("viewPos", camera.Position);
			shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
			shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
			shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

			// material properties
			shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
			shader.setFloat("material.shininess", 64.0f);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);
		}
		break;
	}
	//MVP变换
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)baseManager->screenWidth / (float)baseManager->screenHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 model = getModelMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);

	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube::setType(CubeType _cubeType)
{
	switch (_cubeType)
	{
	case CubeType::withLight:
		shader = Shader("basic_lighting2.vs", "basic_lighting2.fs");
		//法线
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
		glEnableVertexAttribArray(1);
		break;
	case CubeType::withTexture:
		
		break;
	case CubeType::withTexAndLight:
		shader = Shader("lighting_maps.vs", "lighting_maps.fs");
		shader.setInt("material.diffuse", 0);
		//法线
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
		glEnableVertexAttribArray(1);
		//纹理坐标
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//最后一个参数是数据的起点
		glEnableVertexAttribArray(2);
		break;
	}
	cubeType = _cubeType;
}

void Cube::setLightSrc(Node * node)
{
	lightSrc = node;
}

void Cube::setTexture(std::string src)
{
	LoadTexture(diffuseMap, src);
}

Cube::Cube() : cubeType(CubeType::normal)
{
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

