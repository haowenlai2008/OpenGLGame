#include "Material.h"
#include "RenderManager.h"


std::unordered_map<MaterialType, std::string> Material::shaderTypeMap = {
	{MaterialType::PBRCube, "PBRCube"},
	{MaterialType::WithColor, "WithColor"},
	{MaterialType::WithColorAndLight, "WithColorAndLight"},
	{MaterialType::WithTex, "WithTex"},
	{MaterialType::PBR, "PBR"},
	{MaterialType::SimpleDepth, "simpleDepth"},
	{MaterialType::SkyBox, "SkyBox"},
};


unordered_map<MaterialType, Material> Material::systemMaterial = {
	{MaterialType::WithColor,{
		{"mColor", vec3(1.0)},
	}},
	{MaterialType::WithColorAndLight, {}},
	{MaterialType::WithTex, {}},
	{MaterialType::PBR, {
		{"viewPos", vec3(0.0f)},
		{"light.position", vec3(0.0f)},
		{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
		{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
		{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
		{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
		{"material.shininess", 64.0f},
		{"material.diffuse", TextureStructure(TextureType::Texture2D, 0)},
		{"shadowMap", TextureStructure(TextureType::ShadowMap, 1)},
	}},
	{MaterialType::PBRCube, {
		{"viewPos", vec3(0.0f)},
		{"light.position", vec3(0.0f)},
		{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
		{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
		{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
		{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
		{"material.shininess", 64.0f},
		{"material.diffuse", TextureStructure(TextureType::TextureCubMap, 0)},
		{"shadowMap", TextureStructure(TextureType::ShadowMap, 1)},
	}},
	{MaterialType::SimpleDepth, {}},
	{MaterialType::SkyBox, {
		{"material.diffuse", TextureStructure("skybox3", TextureType::TextureCubMap, 0)},
	}},
};

Material::Material(MaterialType materialType)
{
	*this = getSystemMaterial(materialType);
}

Material::Material() : castShadow(false)
{
}


Material::Material(std::initializer_list<pair<string, UniformValue>> uniformList) : 
	castShadow(false),
	m_state_cull()
{
	for (auto& p : uniformList)
	{
		switch (p.second.m_type)
		{
		case UniformType::Bool:
			uniformBool.insert({ p.first, p.second.data.boolData });
			break;
		case UniformType::Int:
			uniformInt.insert({ p.first, p.second.data.intData });
			break;
		case UniformType::Float:
			uniformFloat.insert({ p.first, p.second.data.floatData });
			break;
		case UniformType::Vec2:
			uniformVec2.insert({ p.first, p.second.data.vec2Data });
			break;
		case UniformType::Vec3:
			uniformVec3.insert({ p.first, p.second.data.vec3Data });
			break;
		case UniformType::Vec4:
			uniformVec4.insert({ p.first, p.second.data.vec4Data });
			break;
		case UniformType::Mat2:
			uniformMat2.insert({ p.first, p.second.data.mat2Data });
			break;
		case UniformType::Mat3:
			uniformMat3.insert({ p.first, p.second.data.mat3Data });
			break;
		case UniformType::Mat4:
			uniformMat4.insert({ p.first, p.second.data.mat4Data });
			break;
		case UniformType::Tex:
			// 确定该材质为产生阴影的材质
			if (p.second.texData.m_textureType == TextureType::ShadowMap)
				castShadow = true;
			uniformTex.insert({ p.first, p.second.texData});
			break;
		default:
			break;
		}
	}
}

void Material::bindUniform()
{
	if (m_Shader.expired())
		return;
	auto shader = m_Shader.lock();
	for (auto& pair : uniformBool)
		shader->setBool(pair.first, pair.second);
	for (auto& pair : uniformInt)
		shader->setInt(pair.first, pair.second);
	for (auto& pair : uniformFloat)
		shader->setFloat(pair.first, pair.second);
	for (auto& pair : uniformVec2)
		shader->setVec2(pair.first, pair.second);
	for (auto& pair : uniformVec3)
		shader->setVec3(pair.first, pair.second);
	for (auto& pair : uniformVec4)
		shader->setVec4(pair.first, pair.second);
	for (auto& pair : uniformMat2)
		shader->setMat2(pair.first, pair.second);
	for (auto& pair : uniformMat3)
		shader->setMat3(pair.first, pair.second);
	for (auto& pair : uniformMat4)
		shader->setMat4(pair.first, pair.second);

	// 绑定纹理
	for (auto& pair : uniformTex)
	{
		auto& texInfo = pair.second;
		// 有路径但是没加载的话加载一次
		if (texInfo.m_textureID == ERROR_TEX_ID && texInfo.m_path != "")
		{
			TextureType textureType = texInfo.m_textureType;
			string srcPath = texInfo.m_path;
			GLuint textureID;
			switch (textureType)
			{
			case TextureType::Texture2D:
				textureID = RenderManager::getTexture(srcPath);
				break;
			case TextureType::TextureCubMap:
				textureID = RenderManager::getCubeTexture(srcPath);
				break;
			default:
				std::cout << "Texture " << srcPath << "TypeError" << std::endl;
				break;
			}
			texInfo.m_textureID = textureID;
			std::cout << "Load " << srcPath << std::endl;
		}
		if (texInfo.m_textureID == ERROR_TEX_ID)
			continue;
		shader->setInt(pair.first, pair.second.m_location);
		glActiveTexture(GL_TEXTURE0 + texInfo.m_location);
		GLuint texType = texInfo.m_textureType == TextureType::TextureCubMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;
		glBindTexture(texType, texInfo.m_textureID);
	}
}

void Material::setBool(const string& name, bool value)
{
	uniformBool[name] = value;
}

void Material::setInt(const string& name, int value)
{
	uniformInt[name] = value;
}

void Material::setFloat(const string& name, float value)
{
	uniformFloat[name] = value;
}

void Material::setVec2(const string& name, const vec2& value)
{
	uniformVec2[name] = value;
}

void Material::setVec2(const string& name, float x, float y)
{
	uniformVec2[name] = vec2(x, y);
}

void Material::setVec3(const string& name, const vec3& value)
{
	uniformVec3[name] = value;
}

void Material::setVec3(const string& name, float x, float y, float z)
{
	uniformVec3[name] = vec3(x, y, z);
}

void Material::setVec4(const string& name, const vec4& value)
{
	uniformVec4[name] = value;
}

void Material::setVec4(const string& name, float x, float y, float z, float w)
{
	uniformVec4[name] = vec4(x, y, z, w);
}

void Material::setMat2(const string& name, const glm::mat2& mat)
{
	uniformMat2[name] = mat;
}

void Material::setMat3(const string& name, const glm::mat3& mat)
{
	uniformMat3[name] = mat;
}

void Material::setMat4(const string& name, const glm::mat4& mat)
{
	uniformMat4[name] = mat;
}

void Material::setTexture(const string& name, const string& path, TextureType textureType)
{
	if (uniformTex.find(name) != uniformTex.end())
	{
		uniformTex[name].m_path = path;
		uniformTex[name].m_textureType = textureType;
	}
	else
	{
		uniformTex[name] = TextureStructure(path, textureType, -1);
	}
}

void Material::setTexture(const string& name, const string& path, GLubyte location, TextureType textureType)
{
	uniformTex[name] = TextureStructure(path, textureType, location);
}

void Material::setTextureLocation(const string& name, GLubyte location)
{
	if (uniformTex.find(name) != uniformTex.end())
	{
		uniformTex[name].m_location = location;
	}
	else
	{
		std::cout << "Texture " << name << "doesn't exist" << std::endl;
	}
}

void Material::setTexturePath(const string& name, const string& path)
{
	if (uniformTex.find(name) != uniformTex.end())
	{
		uniformTex[name].m_path = path;
	}
	else
	{
		std::cout << "Texture " << name << "doesn't exist" << std::endl;
	}
}

void Material::setTextureCacheID(const string& name, GLuint cacheID)
{
	if (uniformTex.find(name) != uniformTex.end())
	{
		uniformTex[name].m_textureID = cacheID;
	}
	else
	{
		std::cout << "Texture " << name << "doesn't exist" << std::endl;
	}
}

bool Material::hasTexture(const string& name)
{
	return uniformTex.find(name) != uniformTex.end();
}

Material& Material::getSystemMaterial(MaterialType materialType)
{
	auto& mat = systemMaterial[materialType];
	if (mat.m_Shader.expired())
	{
		mat.m_Shader = Shader::getShader(shaderTypeMap[materialType]);
	}
	return mat;
}
