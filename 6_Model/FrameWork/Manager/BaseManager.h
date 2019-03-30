#pragma once
#include "Shader.h"
#include "Camera.h"
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
	void ProcessInput(GLFWwindow *window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
private:
	GLFWwindow* glWindow;
	void BaseInit();//窗口初始化
	void MainLoop();//主循环
	void Diffuse();//漫反射光
	void Specular();//镜面光
	//编译着色器
	template <typename S1, typename S2 = std::string>
	void ShaderCompile(S1&& vs, S2&& fs)
	{
		ourShader = Shader(std::forward<std::string>(vs), std::forward<std::string>(fs));
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
		std::cout << "nrChannels = " << nrChannels << std::endl;
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
	Shader ourShader;
	Camera myCamera;
	unsigned int VAO;
	unsigned int EBO;
	float screenWidth;
	float screenHeight;
	float lastFrame;
	float deltaTime;
	float lastX;
	float lastY;
	bool firstMouse;
	float view;
	BaseManager();
};