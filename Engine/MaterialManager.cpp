#include "MaterialManager.h"

bool MaterialManager::init()
{
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
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.metallic", 0.8f},
			{"material.roughness", 0.1f},
			{"material.ao", 1.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
			{"irradianceMap", Texture(TextureType::TextureIrradianceMap, 2)},
			{"prefilterMap", Texture(TextureType::TexturePrefilter, 3)},
			{"brdfLUT", Texture(TextureType::TextureBrdfLUT, 4)},
		}},
	};
    return true;
}

Material MaterialManager::getSystemMaterial(string string)
{
	auto mat = Material(systemMaterial[string]);
	if (mat.m_Shader.expired())
	{
		mat.m_Shader = Shader::getShader(shaderTypeMap[string]);
	}
	return mat;
}

Material& MaterialManager::getSystemMaterialRef(string string)
{
	auto& mat = systemMaterial[string];
	if (mat.m_Shader.expired())
	{
		mat.m_Shader = Shader::getShader(shaderTypeMap[string]);
	}
	return mat;
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
