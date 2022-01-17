#pragma once
#include <iostream>
#include <glfw3.h>
#include <glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <stb_image.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "const.h"
using std::vector;
using std::string;

class ResourceTools
{
public:
	//加载纹理
	template <typename S1 = std::string>
	static void LoadTexture(unsigned int& texture, S1&& pic)
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
		unsigned char* data = stbi_load((TEXTURE_PATH + std::forward<std::string>(pic)).c_str(), &width, &height, &nrChannels, 0);
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


	static void LoadCubemap(unsigned int& texture, string&& sboxName, vector<string>& faces = Const::facesName)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(false);
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load((TEXTURE_PATH + sboxName + faces[i]).c_str(),
				&width, &height, &nrChannels, 0);
			std::cout << TEXTURE_PATH + sboxName + faces[i] << std::endl;
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
};

