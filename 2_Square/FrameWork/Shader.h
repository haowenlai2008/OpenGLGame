#ifndef SHADER_H
#define SHADER_H
#include "glfw3.h"
#include "glad.h"; // ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#define TEXTURE_PATH (std::string("Resources/Texture/"))	//�����·��
#define SHADER_PATH (std::string("Resources/Shader/"))		//Shader��·��
//���Shader�Ƿ������ȷ
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
//�����ɫ�������Ƿ������ȷ
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
	// ����ID
	unsigned int ID;
	Shader() : ID(-1)
	{

	};
	// ��������ȡ��������ɫ��
	template <typename S1, typename S2 = std::string>
	Shader(S1&& vertexPath, S2&& fragmentPath)
	{
		// 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ��֤ifstream��������׳��쳣��
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// ���ļ�
			vShaderFile.open(SHADER_PATH + std::forward<S1>(vertexPath));
			fShaderFile.open(SHADER_PATH + std::forward<S2>(fragmentPath));
			std::stringstream vShaderStream, fShaderStream;
			// ��ȡ�ļ��Ļ������ݵ���������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// �ر��ļ�������
			vShaderFile.close();
			fShaderFile.close();
			// ת����������string
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

		// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif