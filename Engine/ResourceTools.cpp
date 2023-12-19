#include "ResourceTools.h"
#include <fstream>

map<string, GLuint> ResourceTools::textures;

unsigned int ResourceTools::getTexture(const string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadTexture(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
		std::cout << "Load " << path << std::endl;
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

unsigned int ResourceTools::getTextureByAbsolutePath(const string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadTextureByAbsolutePath(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
		std::cout << "Load " << path << std::endl;
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

unsigned int ResourceTools::getHDRTexture(const string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadHDRTexture(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
		std::cout << "Load " << path << std::endl;
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

unsigned int ResourceTools::getCubeTexture(const string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadCubemap(result, std::move(path));
		textures.insert(std::pair<string, unsigned int>(path, result));
		std::cout << "Load " << path << std::endl;
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

// 读文件
string ResourceTools::ReadFromFile(const string& path)
{
	std::fstream file;
	file.open(path, std::ios::in);
	string line;
	string result;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			result.append(line);
		}
		file.close();
	}
	return result;
}


// 写文件
void ResourceTools::WriteFile(const string& path, string data)
{
	std::fstream file;
	file.open(path, std::ios::out);
	string line;
	if (file.is_open())
	{
		file << data;
		file.close();
	}
}

std::string indentString(int indentLevel) {
	std::string indent;
	for (int i = 0; i < indentLevel; ++i) {
		indent += "    ";  // 使用四个空格作为缩进
	}
	return indent;
}

string ResourceTools::JsonIndent(const string& jsonString, int indentLevel)
{
	std::string formattedJson;
	size_t length = jsonString.length();
	bool inQuotes = false;
	char prevChar = '\0';

	for (size_t i = 0; i < length; ++i) {
		char currentChar = jsonString[i];

		if (currentChar == '"' && prevChar != '\\') {
			inQuotes = !inQuotes;
		}

		if (!inQuotes) {
			if (currentChar == '}' || currentChar == ']') {
				indentLevel--;
				formattedJson += '\n' + indentString(indentLevel);
			}
		}

		formattedJson += currentChar;

		if (!inQuotes) {
			if (currentChar == '{' || currentChar == '[') {
				indentLevel++;
				formattedJson += '\n' + indentString(indentLevel);
			}
			else if (currentChar == ',' && jsonString[i + 1] != '{' && jsonString[i + 1] != '[') {
				formattedJson += '\n' + indentString(indentLevel);
			}
		}

		prevChar = currentChar;
	}

	return formattedJson;
}
