#include "Shader.h"
#include "BaseManager.h"
#include <string>


//Shader::Shader(std::string&& vertexPath, std::string&& fragmentPath)
//{
//	// 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
//	std::string vertexCode;
//	std::string fragmentCode;
//	std::ifstream vShaderFile;
//	std::ifstream fShaderFile;
//	// ��֤ifstream��������׳��쳣��
//	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//	try
//	{
//		// ���ļ�
//		vShaderFile.open("Resources/Shader/" + vertexPath);
//		fShaderFile.open("Resources/Shader/" + fragmentPath);
//		std::stringstream vShaderStream, fShaderStream;
//		// ��ȡ�ļ��Ļ������ݵ���������
//		vShaderStream << vShaderFile.rdbuf();
//		fShaderStream << fShaderFile.rdbuf();
//		// �ر��ļ�������
//		vShaderFile.close();
//		fShaderFile.close();
//		// ת����������string
//		vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//	}
//	const char* vShaderCode = vertexCode.c_str();
//	const char* fShaderCode = fragmentCode.c_str();
//
//	unsigned int vertex, fragment;
//
//	vertex = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertex, 1, &vShaderCode, NULL);
//	glCompileShader(vertex);
//	assertShader(vertex, "VertexShader");
//
//	fragment = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragment, 1, &fShaderCode, NULL);
//	glCompileShader(fragment);
//	assertShader(fragment, "FragmentShader");
//
//	ID = glCreateProgram();
//	glAttachShader(ID, vertex);
//	glAttachShader(ID, fragment);
//	glLinkProgram(ID);
//
//	assertProgram(ID, "ShaderProgram");
//
//	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
//	glDeleteShader(vertex);
//	glDeleteShader(fragment);
//}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

