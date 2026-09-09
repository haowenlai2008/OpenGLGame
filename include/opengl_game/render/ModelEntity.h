#pragma once
#include "opengl_game/scene/Entity.h"
#include "opengl_game/render/Mesh.h"
class ModelEntity : public Node
{
public:
	CREATE_FUNC(ModelEntity);
	virtual bool init() override;
	virtual void draw() override;
	void setupModel(const string& path, const string& material);
	void modelMaterialUnify();		// 统一材质，开了光滑组可能读不到纹理
};

