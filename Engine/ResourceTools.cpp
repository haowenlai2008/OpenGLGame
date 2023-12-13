#include "ResourceTools.h"

map<string, GLuint> ResourceTools::textures;

unsigned int ResourceTools::getTexture(const string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadTexture(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
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
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}