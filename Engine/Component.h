#pragma once
#include "func.h"
using std::string;
class Entity;
enum class ComponentTypeI	//�������
{
	Shader,
	Physic,
};
enum class ComponentTypeII	//���С��
{
	Shader3D_normal,
	Shader3D_Light,
	Shader3D_Tex,
	Shader3D_TexLight,
	Shader3D_SkyBox,
	Shader2D_Line,
};
class Component : public Ref
{
public:
	LL_SYNTHESIZE(string, tag, Tag);
	LL_SYNTHESIZE(Entity*, entity, Entity);
	LL_SYNTHESIZE(ComponentTypeI, typeI, ComTypeI);	//����
	LL_SYNTHESIZE(ComponentTypeII, typeII, ComTypeII);	//С��
	virtual bool init();
	virtual void use();
	bool operator==(Component& com);
	Component();
	~Component();
};
