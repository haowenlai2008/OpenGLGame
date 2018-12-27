#include "BaseManager.h"
#include "glfw3.h"
#include "glad.h"
#include <iostream>
using namespace std;
BaseManager* BaseManager::m_instance = nullptr;

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
	glfwInit();//≥ı ºªØ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//≈‰÷√GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//≈‰÷√GLFW
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
		0.0f,0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vList), vList, GL_STATIC_DRAW);

	const char *vs = "#version 330 core layout(location = 0) in vec3 aPos;void main(){gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

}
void BaseManager::MainLoop()
{
	while (!glfwWindowShouldClose(glWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ProcessInput(glWindow);
		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}
}
