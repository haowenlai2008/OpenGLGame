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
	void BaseInit();//窗口初始化
	void MainLoop();//主循环
	void ProcessInput(GLFWwindow *window);
	//编译着色器
	template <typename S1, typename S2 = std::string>
	void ShaderCompile(S1&& vs, S2&& fs)
	{
		ourShader = Shader(std::forward<std::string>(vs), std::forward<std::string>(fs));
		shaderProgram = ourShader.ID;
	};
	//加载纹理
	template <typename S1 = std::string>
	void LoadTexture(unsigned int &texture, S1&& pic)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// 加载并生成纹理
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load((TEXTURE_PATH + std::forward<std::string>(pic)).c_str(), &width, &height, &nrChannels, 0);
		std::cout << "nrChannels = " << nrChannels << endl;
		if (data)
		{
			//位深度为24，3个通道(jpg
			if (nrChannels == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//位深度为32，4个通道(png
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
	void Render();//利用顶点索引画两个三角形
	void Render2();//按顺序手动画两个三角形
	void Render3();//使用不同的顶点数组画两个三角形
	void Render4();//彩色三角形
	void Render5();//贴纹理测试
	void Render6();//纹理单元测试
	void Render7();//纹理单元测试(通过上下调整两个纹理的可见度
	Shader ourShader;
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int EBO;
	float view;
	BaseManager();
};