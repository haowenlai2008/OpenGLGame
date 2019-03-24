#include "Shader.h"
#include "glfw3.h"
#include "glad.h"
#include "stb_image.h"
#include <iostream>
using namespace std;

GLFWwindow* glWindow = nullptr;
void BaseInit()
{
	glfwInit();//��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//����GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	float screenWidth = 800.0f;
	float screenHeight = 600.0f;
	//��������
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

	//������ɫ��
	Shader ourShader("vertex_1.vs", "fragment_1.fs");//������ɫ��
	ourShader.use();//ʹ����ɫ��
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO); //���ɶ����������
	glGenBuffers(1, &VBO);//���ɶ��㻺����

	glBindVertexArray(VAO);// �󶨶����������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//�󶨶��㻺����
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);//���û������е�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// ���öԻ��������ʵĲ���Ϊ3�Լ���λΪ0��������ɫ��������������뵽��ɫ���ĵ�һ��(����Ϊ0)������������ݵĳ�����3��float
	glEnableVertexAttribArray(0);



	while (!glfwWindowShouldClose(glWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//��������
		glBindVertexArray(VAO);//�󶨶����������
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