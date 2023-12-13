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
	// ϵͳ���ò��ʣ�ֻ��ͨ��getSystemMaterial��ȡ
	unordered_map<string, std::string> shaderTypeMap;
	unordered_map<string, Material> systemMaterial;
};

