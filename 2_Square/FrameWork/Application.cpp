#include "Shader.h"
#include "glfw3.h"
#include "glad.h"
#include "stb_image.h"
#include <iostream>
using namespace std;

GLFWwindow* glWindow = nullptr;
void BaseInit()
{
	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	float screenWidth = 800.0f;
	float screenHeight = 600.0f;
	//创建窗口
	glWindow = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
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
}
void NormalSquare()
{
	float vertices[] = {
		//     ---- 位置 ----
			 0.5f,  0.5f, 0.0f,  // 右上
			 0.5f, -0.5f, 0.0f,  // 右下
			-0.5f, -0.5f, 0.0f,  // 左下
			-0.5f,  0.5f, 0.0f,  // 左上
	};
	//索引
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	//编译着色器
	Shader ourShader("vertex_2.vs", "fragment_2.fs");
	ourShader.use();//glUseProgram(shaderProgram);
	unsigned int VAO;
	//顶点数组
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//绑定顶点数组缓存
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//绑定索引缓存
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(glWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//draw
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
}

//彩色正方形
void ColourfulSquare()
{
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ---- 
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // 左上
	};
	//索引
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	//编译着色器
	Shader ourShader("vertex_4.vs", "fragment_4.fs");
	ourShader.use();//glUseProgram(shaderProgram);
	unsigned int VAO;
	//顶点数组
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//绑定顶点数组缓存
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//绑定索引缓存
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));	//最后一个参数是数据的起点
	glEnableVertexAttribArray(1);
	//线框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(glWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//draw
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
}
void MainLoop()
{
	ColourfulSquare();
}

int main(int argc, char** argv[])
{
	BaseInit();
	MainLoop();
	return 0;;
}