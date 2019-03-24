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

void MainLoop()
{
	float Triangle[] = {
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
	};

	//编译着色器
	Shader ourShader("vertex_1.vs", "fragment_1.fs");//编译着色器
	ourShader.use();//使用着色器
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO); //生成顶点数组对象
	glGenBuffers(1, &VBO);//生成顶点缓冲区

	glBindVertexArray(VAO);// 绑定顶点数组对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定顶点缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);//设置缓冲区中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// 设置对缓冲区访问的步长为3以及相位为0，告诉着色器，这个数据输入到着色器的第一个(索引为0)输入变量，数据的长度是3个float
	glEnableVertexAttribArray(0);



	while (!glfwWindowShouldClose(glWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//画三角形
		glBindVertexArray(VAO);//绑定顶点数组对象
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}
}
int main(int argc, char** argv[])
{
	BaseInit();
	MainLoop();
	return 0;;
}