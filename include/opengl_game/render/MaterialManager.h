#pragma once
#include <unordered_map>
#include "Material.h"
#include "Singleton.h"
#include "json.hpp"

using json = nlohmann::json;
class MaterialManager : public Singleton<MaterialManager>
{
public:
	friend class Singleton<MaterialManager>;
	bool init();
	Material getSystemMaterial(const string& key);
	Material& getSystemMaterialRef(const string& key);
	Material getUserMaterial(const string& key);
	Material& getUserMaterialRef(const string& key);

private:
	// 系统内置材质，只能通过getSystemMaterial获取
	unordered_map<string, std::string> shaderTypeMap;
	unordered_map<string, Material> systemMaterial;
	unordered_map<string, Material> userMaterial;
	static json SerializeMaterial(const string& matName, const string& shaderName, const Material& mat);
	static Material DeserializeJsonToMaterial(const string& jsonStr);
};

