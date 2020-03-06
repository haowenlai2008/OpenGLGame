#ifndef SHADER_H
#define SHADER_H
#include "func.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>
using std::map;
using std::string;

//检查Shader是否编译正确
static void assertShader(unsigned int shaderObj, std::string&& shaderName)
{
	int success = 0;
	char infoLog[512];
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
		std::cout << shaderName << "   ";
		std::cout << "ERROR::SHADER" << shaderName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
//检查着色器程序是否编译正确
static void assertProgram(unsigned int programObj, std::string&& programName)
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
	~Shader() {};
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
			vShaderFile.open(std::forward<S1>(vertexPath));
			fShaderFile.open(std::forward<S2>(fragmentPath));
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
	//获得着色器
	static std::shared_ptr<Shader>& getShader(string&& shaderName)
	{
		if (shaderMap.find(shaderName) != shaderMap.end())
		{
			return shaderMap[shaderName];
			
		}
		else
		{
			std::shared_ptr<Shader> shader(new Shader(SHADER_PATH + shaderName + ".vs", SHADER_PATH + shaderName + ".fs"));
			shaderMap.insert(std::pair<string, std::shared_ptr<Shader>>(shaderName, shader));
			return shaderMap[shaderName];
		}
	}

	//获得着色器
	static std::shared_ptr<Shader>& getShader(const string& shaderName)
	{
		if (shaderMap.find(shaderName) != shaderMap.end())
		{
			return shaderMap[shaderName];

		}
		else
		{
			std::shared_ptr<Shader> shader(new Shader(SHADER_PATH + shaderName + ".vs", SHADER_PATH + shaderName + ".fs"));
			shaderMap.insert(std::pair<string, std::shared_ptr<Shader>>(shaderName, shader));
			return shaderMap[shaderName];
		}
	}
	//获得滤镜
	static std::shared_ptr<Shader>& getFilter(string&& filterName)
	{
		if (shaderMap.find(filterName) != shaderMap.end())
		{
			return shaderMap[filterName];

		}
		else
		{
			std::shared_ptr<Shader> shader(new Shader(FILTER_VS, FILTER_PATH + filterName + ".fs"));
			shaderMap.insert(std::pair<string, std::shared_ptr<Shader>>(filterName, shader));
			return shaderMap[filterName];
		}
	}
	Shader(Shader&& rref) { ID = rref.ID, rref.ID = -1; };
	Shader(const Shader& lref) { ID = lref.ID; };
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

private:
	static map<string, std::shared_ptr<Shader>> shaderMap;
};

#endif