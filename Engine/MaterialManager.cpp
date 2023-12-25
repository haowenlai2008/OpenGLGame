#include "MaterialManager.h"


// 序列化用映射
static std::map<TextureType, std::string> textureTypeToString = {
	{TextureType::Texture2D, "Texture2D"},
	{TextureType::TextureHDR, "TextureHDR"},
	{TextureType::TextureEnv, "TextureEnv"},
	{TextureType::TextureCubMap, "TextureCubMap"},
	{TextureType::TextureIrradianceMap, "TextureIrradianceMap"},
	{TextureType::TexturePrefilter, "TexturePrefilter"},
	{TextureType::TextureBrdfLUT, "TextureBrdfLUT"},
	{TextureType::GBufferPos, "GBufferPos"},
	{TextureType::GBufferNormal, "GBufferNormal"},
	{TextureType::GBufferAlbedo, "GBufferAlbedo"},
	{TextureType::GBufferMetallicRoughness, "GBufferMetallicRoughness"},
	{TextureType::GBufferPosLightSpace, "GBufferPosLightSpace"},
	{TextureType::SSAOTexture, "SSAOTexture"},
};


// 反序列化用映射
static std::map<std::string, TextureType> stringToTextureType = {
	{"Texture2D", TextureType::Texture2D},
	{"TextureHDR", TextureType::TextureHDR},
	{"TextureEnv", TextureType::TextureEnv},
	{"TextureCubMap", TextureType::TextureCubMap},
	{"TextureIrradianceMap", TextureType::TextureIrradianceMap},
	{"TexturePrefilter", TextureType::TexturePrefilter},
	{"GBufferPos", TextureType::GBufferPos},
	{"GBufferNormal", TextureType::GBufferNormal},
	{"GBufferAlbedo", TextureType::GBufferAlbedo},
	{"GBufferMetallicRoughness", TextureType::GBufferMetallicRoughness},
	{"GBufferPosLightSpace", TextureType::GBufferPosLightSpace},
	{"SSAOTexture", TextureType::SSAOTexture},
};

bool MaterialManager::init()
{
	userMaterial = {};

	shaderTypeMap = {
		{"PBRCube", "PBRCube"},
		{"WithColor", "WithColor"},
		{"WithColorAndLight", "WithColorAndLight"},
		{"WithTex", "WithTex"},
		{"WithTexAndLight", "WithTexAndLight"},
		{"PBR", "PBR"},
		{"SimpleDepth", "simpleDepth"},
		{"SkyBox", "SkyBox"},
		{"SkyBoxHDR", "SkyBoxHDR"},
		{"EquirectangularToCubemap", "IBL_EquirectangularToCubemap"},
		{"ModelPBR", "PBRModel"},
		{"IBL_PBR", "IBL_PBR"},
		{"Deferred_Render", "Deferred_Render"},
		{"Deferred_SSAO", "Deferred_SSAO"},
	};

	systemMaterial = {
		{"WithColor",{
			{"mColor", vec3(1.0)},
		}},
		{"WithColorAndLight", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
		{"WithTex", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
		}},

		{"WithTexAndLight", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
		{"PBR", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"light.intensity", 200.0f},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.metallic", 0.5f},
			{"material.roughness", 0.2f},
			{"material.ao", 1.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
		{"PBRCube", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"light.intensity", 200.0f},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.metallic", 0.5f},
			{"material.roughness", 0.2f},
			{"material.ao", 1.0f},
			{"material.diffuse", Texture(TextureType::TextureCubMap, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
		{"SimpleDepth", {}},
		{"SkyBox", {
			//{"material.diffuse", Texture("skybox3", TextureType::TextureCubMap, 0)},
			{"material.diffuse", Texture(TextureType::TextureEnv, 0)},
			{"environmentMap", Texture(TextureType::TextureEnv, 1)},
		}},
		{"SkyBoxHDR", {
			{"equirectangularMap", Texture("Alexs_Apartment/Alexs_Apt_2k.hdr", TextureType::TextureHDR, 0)},
		}},
		{"EquirectangularToCubemap", {
			{"equirectangularMap", Texture("Alexs_Apartment/Alexs_Apt_2k.hdr", TextureType::TextureHDR, 0)},
		}},
		{"ModelPBR", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"light.intensity", 100.0f},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.metallic", 0.01f},
			{"material.roughness", 0.6f},
			{"material.ao", 1.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
		{"IBL_PBR", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"light.intensity", 100.0f},
			{"material.metallic", 0.7f},
			{"material.roughness", 0.1f},
			{"material.ao", 1.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
			{"irradianceMap", Texture(TextureType::TextureIrradianceMap, 2)},
			{"prefilterMap", Texture(TextureType::TexturePrefilter, 3)},
			{"brdfLUT", Texture(TextureType::TextureBrdfLUT, 4)},
		}},
		{ "Deferred_Render", {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"light.intensity", 100.0f},
			{"gBuffer.pos", Texture(TextureType::GBufferPos, 0)},
			{"gBuffer.normal", Texture(TextureType::GBufferNormal, 1)},
			{"gBuffer.metal_rough", Texture(TextureType::GBufferMetallicRoughness, 2)},
			{"gBuffer.albedo", Texture(TextureType::GBufferAlbedo, 3)},
			{"gBuffer.posLightSpace", Texture(TextureType::GBufferPosLightSpace, 4)},
			{"shadowMap", Texture(TextureType::ShadowMap, 5)},
			{"irradianceMap", Texture(TextureType::TextureIrradianceMap, 6)},
			{"prefilterMap", Texture(TextureType::TexturePrefilter, 7)},
			{"brdfLUT", Texture(TextureType::TextureBrdfLUT, 8)},
		}},
		{ "Deferred_SSAO", {
			{"gBuffer.pos", Texture(TextureType::GBufferPos, 0)},
			{"gBuffer.normal", Texture(TextureType::GBufferNormal, 1)},
		} },
	};
	
	// 系统材质写入到json
	//for (auto [matName, mat] : systemMaterial)
	//{
	//	if (shaderTypeMap.find(matName) != shaderTypeMap.end())
	//	{
	//		json jsonData = SerializeMaterial(matName, shaderTypeMap[matName], mat);
	//		string jsonStr = ResourceTools::JsonIndent(nlohmann::to_string(jsonData));
	//		ResourceTools::WriteFile(MATERIAL_PATH + matName + ".json", jsonStr);
	//	}
	//}

    return true;
}

Material MaterialManager::getSystemMaterial(const string& key)
{
	auto mat = Material(systemMaterial[key]);
	if (mat.m_Shader.expired())
	{
		mat.m_Shader = Shader::getShader(shaderTypeMap[key]);
	}
	return mat;
}

Material& MaterialManager::getSystemMaterialRef(const string& key)
{
	auto& mat = systemMaterial[key];
	if (mat.m_Shader.expired())
	{
		mat.m_Shader = Shader::getShader(shaderTypeMap[key]);
	}
	return mat;
}

Material MaterialManager::getUserMaterial(const string& key)
{
	auto resultIt = userMaterial.find(key);
	if (resultIt != userMaterial.end())
		return userMaterial[key];
	string path = MATERIAL_PATH + key + ".json";
	string result = ResourceTools::ReadFromFile(path);
	assert(!result.empty());
	userMaterial[key] = DeserializeJsonToMaterial(result);
	return userMaterial[key];
}

Material& MaterialManager::getUserMaterialRef(const string& key)
{
	auto resultIt = userMaterial.find(key);
	if (resultIt != userMaterial.end())
		return userMaterial[key];
	string path = MATERIAL_PATH + key + ".json";
	string result = ResourceTools::ReadFromFile(path);
	assert(!result.empty());
	userMaterial[key] = DeserializeJsonToMaterial(result);
	return userMaterial[key];
}

// 材质序列化
json MaterialManager::SerializeMaterial(const string& matName, const string& shaderName, const Material& mat)
{

	json jsonObj;
	jsonObj["MatName"] = matName;
	jsonObj["ShaderName"] = shaderName;
	jsonObj["UniformBool"] = {};
	jsonObj["UniformInt"] = {};
	jsonObj["UniformFloat"] = {};
	jsonObj["UniformVec2"] = {};
	jsonObj["UniformVec3"] = {};
	jsonObj["UniformVec4"] = {};
	jsonObj["UniformMat2"] = {};
	jsonObj["UniformMat3"] = {};
	jsonObj["UniformMat4"] = {};
	jsonObj["UniformTexture"] = {};

	for (auto [uniformName, value] : mat.uniformBool)
		jsonObj["UniformBool"][uniformName] = value;
	for (auto [uniformName, value] : mat.uniformInt)
		jsonObj["UniformInt"][uniformName] = value;
	for (auto [uniformName, value] : mat.uniformFloat)
		jsonObj["UniformFloat"][uniformName] = value;

	for (auto [uniformName, value] : mat.uniformVec2)
	{
		jsonObj["UniformVec2"][uniformName] = {};
		jsonObj["UniformVec2"][uniformName]["x"] = value.x;
		jsonObj["UniformVec2"][uniformName]["y"] = value.y;
	}

	for (auto [uniformName, value] : mat.uniformVec3)
	{
		jsonObj["UniformVec3"][uniformName] = {};
		jsonObj["UniformVec3"][uniformName]["x"] = value.x;
		jsonObj["UniformVec3"][uniformName]["y"] = value.y;
		jsonObj["UniformVec3"][uniformName]["z"] = value.z;
	}
	for (auto [uniformName, value] : mat.uniformVec4)
	{
		jsonObj["UniformVec3"][uniformName] = {};
		jsonObj["UniformVec3"][uniformName]["x"] = value.x;
		jsonObj["UniformVec3"][uniformName]["y"] = value.y;
		jsonObj["UniformVec3"][uniformName]["z"] = value.z;
		jsonObj["UniformVec3"][uniformName]["w"] = value.w;
	}

	for (auto [uniformName, value] : mat.uniformMat2)
	{
		jsonObj["UniformMat2"][uniformName] = {};
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
			{
				string key = std::to_string(i) + std::to_string(j);
				jsonObj["UniformMat"][uniformName][key] = value[i][j];
			}
	}

	for (auto [uniformName, value] : mat.uniformMat3)
	{
		jsonObj["UniformMat3"][uniformName] = {};
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				string key = std::to_string(i) + std::to_string(j);
				jsonObj["UniformMat3"][uniformName][key] = value[i][j];
			}
	}

	for (auto [uniformName, value] : mat.uniformMat4)
	{
		jsonObj["UniformMat4"][uniformName] = {};
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				string key = std::to_string(i) + std::to_string(j);
				jsonObj["UniformMat4"][uniformName][key] = value[i][j];
			}
	}


	for (auto [uniformName, value] : mat.uniformTex)
	{
		jsonObj["UniformTexture"][uniformName] = {};
		jsonObj["UniformTexture"][uniformName]["TextureType"] = textureTypeToString[value.m_textureType];
		jsonObj["UniformTexture"][uniformName]["Location"] = value.m_location;
		jsonObj["UniformTexture"][uniformName]["Path"] = value.m_path;
	}
	return jsonObj;

}

Material MaterialManager::DeserializeJsonToMaterial(const string& jsonStr)
{
	json jsonObj = json::parse(jsonStr);
	Material result;
	result.m_shaderName = jsonObj["ShaderName"];
	result.m_matName = jsonObj["MatName"];
	result.m_Shader = Shader::getShader(jsonObj["ShaderName"]);

	for (auto it = jsonObj["UniformBool"].begin(); it != jsonObj["UniformBool"].end(); ++it)
		result.uniformBool[it.key()] = it.value();

	for (auto it = jsonObj["UniformInt"].begin(); it != jsonObj["UniformInt"].end(); ++it)
		result.uniformInt[it.key()] = it.value();

	for (auto it = jsonObj["UniformFloat"].begin(); it != jsonObj["UniformFloat"].end(); ++it)
		result.uniformFloat[it.key()] = it.value();

	for (auto it = jsonObj["UniformVec2"].begin(); it != jsonObj["UniformVec2"].end(); ++it)
	{
		result.uniformVec2[it.key()] = vec2(it.value()["x"], it.value()["y"]);
	}

	for (auto it = jsonObj["UniformVec3"].begin(); it != jsonObj["UniformVec3"].end(); ++it)
	{
		result.uniformVec3[it.key()] = vec3(it.value()["x"], it.value()["y"], it.value()["z"]);
	}

	for (auto it = jsonObj["UniformVec4"].begin(); it != jsonObj["UniformVec4"].end(); ++it)
	{
		result.uniformVec4[it.key()] = vec4(it.value()["x"], it.value()["y"], it.value()["z"], it.value()["w"]);
	}

	for (auto it = jsonObj["UniformMat2"].begin(); it != jsonObj["UniformMat2"].end(); ++it)
	{
		auto matValue = it.value();
		mat2 matData = mat2();
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
			{
				string key = std::to_string(i) + std::to_string(j);
				matData[i][j] = matValue[key];
			}
		result.uniformMat2[it.key()] = matData;
	}

	for (auto it = jsonObj["UniformMat3"].begin(); it != jsonObj["UniformMat3"].end(); ++it)
	{
		auto matValue = it.value();
		mat3 matData = mat3();
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				string key = std::to_string(i) + std::to_string(j);
				matData[i][j] = matValue[key];
			}
		result.uniformMat3[it.key()] = matData;
	}

	for (auto it = jsonObj["UniformMat4"].begin(); it != jsonObj["UniformMat4"].end(); ++it)
	{
		auto matValue = it.value();
		mat4 matData = mat4();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				string key = std::to_string(i) + std::to_string(j);
				matData[i][j] = matValue[key];
			}
		result.uniformMat4[it.key()] = matData;
	}



	for (auto it = jsonObj["UniformTexture"].begin(); it != jsonObj["UniformTexture"].end(); ++it)
	{
		auto matValue = it.value();
		GLuint location = matValue["Location"];
		string path = matValue["Path"];
		TextureType textureType = stringToTextureType[matValue["TextureType"]];
		result.uniformTex[it.key()] = Texture(path, textureType, location);
	}
	return result;
}


//Material& MaterialManager::createMaterial(const string& matKey)
//{
//	// TODO: 在此处插入 return 语句
//}
//
//Material& MaterialManager::createMaterial(const string& matKey, string string)
//{
//	return Material();
//}
