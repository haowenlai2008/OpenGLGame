#pragma once
#include <unordered_map>
#include "Material.h"
#include "Singleton.h"


class MaterialManager : public Singleton<MaterialManager>
{
public:
	friend class Singleton<MaterialManager>;
	bool init();
	Material getSystemMaterial(string string);
	Material& getSystemMaterialRef(string string);
	//Material& createMaterial(const string& matKey);
	//Material& createMaterial(const string& matKey, string string);
private:
	// 系统内置材质，只能通过getSystemMaterial获取
	unordered_map<string, std::string> shaderTypeMap;
	unordered_map<string, Material> systemMaterial;
};

