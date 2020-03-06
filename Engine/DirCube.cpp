#include "DirCube.h"
#include "BaseManager.h"
#include "SkyBox.h"
using std::endl;
using std::cout;
vector<float> DirCube::vertex  = {
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
DirCube * DirCube::create(CubeType _cubeType, vec3 _target)
{
	DirCube *pRet = new(std::nothrow) DirCube();
	pRet->target = _target;
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
bool DirCube::init()
{
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);

	//glBindVertexArray(VAO);// 绑定顶点数组对象
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定顶点缓冲区
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.begin()._Ptr, GL_STATIC_DRAW);
	////坐标
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
	//glEnableVertexAttribArray(0);
	////法线
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	////纹理坐标
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//switch (cubeType)
	//{
	//case CubeType::normal:
	//	addComponent(new Shader3D_normal());
	//	break;
	//case CubeType::withLight:
	//	addComponent(new Shader3D_Light());
	//	break;
	//case CubeType::withTexture:
	//	addComponent(new Shader3D_Tex());
	//	break;
	//case CubeType::withTexAndLight:
	//	addComponent(new Shader3D_TexLight());
	//	break;
	//case CubeType::withSkyBox:
	//	addComponent(new Shader3D_SkyBox());
	//	break;
	//default:
	//	break;
	//}
	return true;
}

void DirCube::draw()
{
	glBindVertexArray(m_VAO);
	Entity::draw();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void DirCube::setType(CubeType _cubeType)
{
	//switch (_cubeType)
	//{
	//case CubeType::normal:
	//	setComponent(Shader3D_normal::create());
	//case CubeType::withLight:
	//	setComponent(Shader3D_Light::create());
	//	break;
	//case CubeType::withTexture:
	//	setComponent(Shader3D_Tex::create());
	//	break;
	//case CubeType::withTexAndLight:
	//	setComponent(Shader3D_TexLight::create());
	//	break;
	//case CubeType::withSkyBox:
	//	setComponent(Shader3D_SkyBox::create());
	//	break;
	//default:
	//	setComponent(Shader3D_normal::create());
	//}
	//cubeType = _cubeType;
}

void DirCube::update(float delta)
{
	if (!isArrive)
	{
		vec3 dir = target - transform.position;
		transform.position += glm::normalize(dir) * 0.4f;
		
		if (glm::length(dir) < 2.0f)
		{
			isArrive = true;
			transform.position = target;
		}	
	}
	
}

DirCube::DirCube() : cubeType(CubeType::normal), target(vec3(0.0f,0.0f,0.0f)), isArrive(false)
{
}

DirCube::~DirCube()
{
	
}

