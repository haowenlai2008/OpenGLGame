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
	// ϵͳ���ò��ʣ�ֻ��ͨ��getSystemMaterial��ȡ
	vector<MaterialType> specialTexture;
	unordered_map<MaterialType, std::string> shaderTypeMap;
	unordered_map<MaterialType, Material> systemMaterial;
};

