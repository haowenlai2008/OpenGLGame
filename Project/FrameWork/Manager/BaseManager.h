#pragma once
#include "Shader.h"
#include "glfw3.h"
#include "glad.h"
#include "stb_image.h"
#include "const.h"
#include <iostream>
class GLFWwindow;
class BaseManager
{
public:
	static BaseManager* m_instance;
	~BaseManager();
	static BaseManager* getInstance();
	int Run();
private:
	GLFWwindow* glWindow;
	void BaseInit();//���ڳ�ʼ��
	void MainLoop();//��ѭ��
	void ProcessInput(GLFWwindow *window);
	//������ɫ��
	template <typename S1, typename S2 = std::string>
	void ShaderCompile(S1&& vs, S2&& fs)
	{
		ourShader = Shader(std::forward<std::string>(vs), std::forward<std::string>(fs));
		shaderProgram = ourShader.ID;
	};
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
	void Render();//���ö�������������������
	void Render2();//��˳���ֶ�������������
	void Render3();//ʹ�ò�ͬ�Ķ������黭����������
	void Render4();//��ɫ������
	void Render5();//���������
	void Render6();//����Ԫ����
	void Render7();//����Ԫ����(ͨ�����µ�����������Ŀɼ���
	Shader ourShader;
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int EBO;
	float view;
	BaseManager();
};