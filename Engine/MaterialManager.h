#pragma once
#include <unordered_map>
#include "Material.h"
#include "Singleton.h"

class MaterialManager : public Singleton<MaterialManager>
{
public:
	friend class Singleton<MaterialManager>;
	bool init();
	Material& getSystemMaterial(MaterialType materialType);
private:
	// 系统内置材质，只能通过getSystemMaterial获取
	vector<MaterialType> specialTexture;
	unordered_map<MaterialType, std::string> shaderTypeMap;
	unordered_map<MaterialType, Material> systemMaterial;
};

