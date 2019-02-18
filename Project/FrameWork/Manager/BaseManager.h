#pragma once
#include "Shader.h"
#include "const.h"
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
	void BaseInit();
	void MainLoop();
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
		unsigned char *data = stbi_load((TEXTURE_PATH + std::forward<std::string>(pic)).c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		data = nullptr;
	}
	void RenderInit5();
	void Render();
	void Render2();
	void Render3();
	void Render4();//��ɫ������
	void Render5();//������
	Shader ourShader;
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int Texture;
	BaseManager();
};