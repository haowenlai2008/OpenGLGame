#include "Shader.h"
#include "glfw3.h"
#include "glad.h"
#include "stb_image.h"
#include <iostream>
using namespace std;
//����ģʽ
enum class SurroundMode
{
	Repeat = GL_REPEAT,						//�ظ�����ͼ��
	MirroredRepeat = GL_MIRRORED_REPEAT,	//�����ظ�����ͼ��
	ClampToEdge = GL_CLAMP_TO_EDGE,			//����Ե����
	ClampToBoreder = GL_CLAMP_TO_BORDER		//�����Ĳ���Ϊָ����Ե��ɫ
};
//���˷�ʽ
enum class FilteringMode
{
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
};
GLFWwindow* glWindow = nullptr;
//��������
template <typename S1 = std::string>
void LoadTexture(unsigned int &texture, S1&& pic)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ���ز���������
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load((TEXTURE_PATH + std::forward<std::string>(pic)).c_str(), &width, &height, &nrChannels, 0);
	std::cout << "nrChannels = " << nrChannels << endl;
	if (data)
	{
		//λ���Ϊ24��3��ͨ��(jpg
		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//λ���Ϊ32��4��ͨ��(png
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	data = nullptr;
}
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
void NormalSquare()
{
	float vertices[] = {
		//     ---- λ�� ----
			 0.5f,  0.5f, 0.0f,  // ����
			 0.5f, -0.5f, 0.0f,  // ����
			-0.5f, -0.5f, 0.0f,  // ����
			-0.5f,  0.5f, 0.0f,  // ����
	};
	//����
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	//������ɫ��
	Shader ourShader("vertex_1.vs", "fragment_1.fs");
	ourShader.use();//glUseProgram(shaderProgram);
	unsigned int VAO;
	//��������
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//�󶨶������黺��
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//����������
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// λ������
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

//��ɫ������
void ColourfulSquare()
{
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ---- 
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // ����
	};
	//����
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	//������ɫ��
	Shader ourShader("vertex_4.vs", "fragment_4.fs");
	ourShader.use();//glUseProgram(shaderProgram);
	unsigned int VAO;
	//��������
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//�󶨶������黺��
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//����������
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));	//���һ�����������ݵ����
	glEnableVertexAttribArray(1);
	//�߿�ģʽ
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