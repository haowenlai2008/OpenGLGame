#ifndef SHADER_H
#define SHADER_H
#include "glfw3.h"
#include "glad.h"; // 包含glad来获取所有的必须OpenGL头文件
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "const.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

//检查Shader是否编译正确
inline void assertShader(unsigned int shaderObj, std::string&& shaderName)
{
	int success = 0;
	char infoLog[512];
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER" << shaderName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
//检查着色器程序是否编译正确
inline void assertProgram(unsigned int programObj, std::string&& programName)
{
	int success = 0;
	char infoLog[512];
	glGetProgramiv(programObj, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(programObj, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::" << programName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
class Shader
{
public:
	// 程序ID
	unsigned int ID;
	Shader() : ID(-1)
	{

	};
	// 构造器读取并构建着色器
	template <typename S1, typename S2 = std::string>
	Shader(S1&& vertexPath, S2&& fragmentPath)
	{
		// 1. 从文件路径中获取顶点/片段着色器
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// 保证ifstream对象可以抛出异常：
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// 打开文件
			vShaderFile.open(SHADER_PATH + std::forward<S1>(vertexPath));
			fShaderFile.open(SHADER_PATH + std::forward<S2>(fragmentPath));
			std::stringstream vShaderStream, fShaderStream;
			// 读取文件的缓冲内容到数据流中
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// 关闭文件处理器
			vShaderFile.close();
			fShaderFile.close();
			// 转换数据流到string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		assertShader(vertex, "VertexShader");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		assertShader(fragment, "FragmentShader");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		assertProgram(ID, "ShaderProgram");

		// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// 使用/激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
};

#endif