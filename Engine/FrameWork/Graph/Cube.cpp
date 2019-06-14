#include "Cube.h"
#include "BaseManager.h"
#include "SkyBox.h"
#include "all3DShader.h"
using std::endl;
using std::cout;
vector<float> Cube::vertex  = {
		// Back face
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // bottom-right         
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top-right
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // top-left
		// Front face
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // top-right
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // top-right
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // top-left
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
		// Left face
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // top-right
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-left
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // bottom-left
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // bottom-left
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // top-right
		// Right face
		0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // bottom-right
		0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // top-right         
		0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // bottom-right
		0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // top-left
		0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // bottom-left     
		// Bottom face
	   -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // top-left
		0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // bottom-left
	   -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // bottom-right
	   -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // top-right
		// Top face
	   -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // top-left
		0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // bottom-right
		0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,   1.0f, 1.0f, // top-right     
		0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // bottom-right
	   -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // top-left
	   -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,   0.0f, 0.0f  // bottom-left  
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
	//坐标
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	//法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	switch (cubeType)
	{
	case CubeType::normal:
		//cout << "2333" << std::endl;
		addComponent(new Shader3D_normal());
		break;
	case CubeType::withLight:
		addComponent(new Shader3D_Light());
		break;
	case CubeType::withTexture:
		addComponent(new Shader3D_Tex());
		break;
	case CubeType::withTexAndLight:
		addComponent(new Shader3D_TexLight());
		break;
	case CubeType::withSkyBox:
		addComponent(new Shader3D_SkyBox());
		break;
	default:
		break;
	}
	//switch (cubeType)
	//{
	//case CubeType::normal:
	//	shader = Shader::getShader("normal");
	//	break;
	//case CubeType::withLight:
	//	shader = Shader::getShader("withLight");
	//	//法线
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
	//	glEnableVertexAttribArray(1);
	//	break;
	//case CubeType::withTexture:
	//	shader = Shader::getShader("withTexture");
	//	//纹理坐标
	//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//最后一个参数是数据的起点
	//	glEnableVertexAttribArray(1);
	//	break;
	//case CubeType::withTexAndLight:
	//	shader = Shader::getShader("withTexAndLight");
	//	shader.setInt("material.diffuse", 0);
	//	//法线
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
	//	glEnableVertexAttribArray(1);
	//	//纹理坐标
	//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//最后一个参数是数据的起点
	//	glEnableVertexAttribArray(2);
	//	break;
	//case CubeType::withSkyBox:
	//	shader = Shader::getShader("withSkyBox");
	//	//法线
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
	//	glEnableVertexAttribArray(1);
	//	break;
	//}
	//shader.use();
	//shader = Shader::getShader("normal");
	
	return true;
}

void Cube::draw()
{
	//shader.use();
	glBindVertexArray(VAO);
	//BaseManager* baseManager = BaseManager::getInstance();
	//Camera& camera = *baseManager->getCamera();
	//glBindVertexArray(VAO);
	//
	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)baseManager->screenWidth / (float)baseManager->screenHeight, 0.1f, 100.0f);
	//glm::mat4 view = camera.GetViewMatrix();
	//glm::mat4 model = getModelMatrix();
	//shader.setMat4("projection", projection);
	//shader.setMat4("view", view);
	//shader.setMat4("model", model);
	//shader.setVec3("aColor", getColor());
	Entity::draw();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube::setType(CubeType _cubeType)
{
	switch (_cubeType)
	{
	case CubeType::normal:
		setComponent(Shader3D_normal::create());
	case CubeType::withLight:
		setComponent(Shader3D_Light::create());
		break;
	case CubeType::withTexture:
		setComponent(Shader3D_Tex::create());
		break;
	case CubeType::withTexAndLight:
		setComponent(Shader3D_TexLight::create());
		break;
	case CubeType::withSkyBox:
		setComponent(Shader3D_SkyBox::create());
		break;
	default:
		setComponent(Shader3D_normal::create());
	}
	cubeType = _cubeType;
}


Cube::Cube() : cubeType(CubeType::normal)
{
}

Cube::~Cube()
{
	
}

