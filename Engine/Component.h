#pragma once
#include <iostream>
#include <string>
#include "Ref.h"
#include "func.h"
using std::string;
class Entity;
enum class ComponentTypeI	//组件大类
{
	Shader,
	Physic,
};
enum class ComponentTypeII	//组件小类
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
	LL_SYNTHESIZE(ComponentTypeI, typeI, ComTypeI);	//大类
	LL_SYNTHESIZE(ComponentTypeII, typeII, ComTypeII);	//小类
	virtual bool init();
	virtual void use();
	bool operator==(Component& com);
	Component();
	~Component();
};
