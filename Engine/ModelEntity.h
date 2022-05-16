#pragma once
#include "Entity.h"
class ModelEntity : public Entity
{
public:
	CREATE_FUNC(ModelEntity);
	ENTITY_CREATE_FUNC(ModelEntity);
	virtual bool init() override;
	void setupModel(const string& path);
};

