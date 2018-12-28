#include "BaseManager.h"
#include "glfw3.h"
#include "glad.h"
#include <iostream>
#include <string>
using namespace std;
BaseManager* BaseManager::m_instance = nullptr;

inline void assertShader(unsigned int shaderObj, std::string&& shaderName)
{
	int success = 0;
	char infoLog[512];
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER"<< shaderName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

inline void assertProgram(unsigned int programObj, std::string&& programName)
{
	int success = 0;
	char infoLog[512];
	glGetProgramiv(programObj, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(programObj, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::" << programName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
BaseManager::BaseManager()
{
}


BaseManager::~BaseManager()
{
}

BaseManager * BaseManager::getInstance()
{
	if (!m_instance)
		m_instance = new(std::nothrow) BaseManager();
	return m_instance;
}

int BaseManager::Run()
{
	BaseInit();
	MainLoop();
	return 0;
}

void BaseManager::BaseInit()
{
	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	glWindow = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (glWindow == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(glWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glfwSetFramebufferSizeCallback(glWindow, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
}
void BaseManager::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void BaseManager::Render()
{
	float vList[] = {
		0.5f,0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		-0.5f,0.5f,0.0f,
		0.0f,0.7f,0.0f
	};

	unsigned int indices[] = {
		0,1,4,
		1,2,3
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vList), vList, GL_STATIC_DRAW);

	const char *vs = "#version 330 core \n layout(location = 0) in vec3 aPos; void main(){gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}";
	//顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);
	assertShader(vertexShader,"VertexShader");
	//片段着色器
	const char* fs = "#version 330 core \n out vec4 FragColor; \n void main(){FragColor=vec4(1.0f,0.5f,0.2f,1.0f);}";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, nullptr);
	glCompileShader(fragmentShader);
	assertShader(fragmentShader, "FragmentShader");
	//着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	assertProgram(shaderProgram, "ShaderProgram");
	//清理vs，fs
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//绑定顶点数组缓存
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vList), vList, GL_STATIC_DRAW);
	//索引缓存
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	//绑定索引
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgram);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void BaseManager::Render2()
{
	float vList[] = {
		0.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		0.8f,0.8f,0.0f,
		0.8f,-0.5f,0.0f,
		0.0f,0.7f,0.0f
	};

	//unsigned int indices[] = {
	//	0,1,4,
	//	1,2,3
	//};
	

	const char *vs = "#version 330 core \n layout(location = 0) in vec3 aPos; void main(){gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}";
	//顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);
	assertShader(vertexShader, "VertexShader");
	//片段着色器
	const char* fs = "#version 330 core \n out vec4 FragColor; \n void main(){FragColor=vec4(1.0f,0.5f,0.2f,1.0f);}";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, nullptr);
	glCompileShader(fragmentShader);
	assertShader(fragmentShader, "FragmentShader");
	//着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	assertProgram(shaderProgram, "ShaderProgram");
	//清理vs，fs
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vList), vList, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//绑定顶点数组缓存
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vList), vList, GL_STATIC_DRAW);


	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//线框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLES,0,6);
	glBindVertexArray(0);
}

void BaseManager::MainLoop()
{
	while (!glfwWindowShouldClose(glWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Render2();
		ProcessInput(glWindow);
		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}
}
