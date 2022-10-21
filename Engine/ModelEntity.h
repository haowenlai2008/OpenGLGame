#pragma once
#include "Entity.h"
#include "Mesh.h"
class Model;
class ModelEntity : public Node
{
public:
	CREATE_FUNC(ModelEntity);
	virtual bool init() override;
	virtual void draw() override;
	void setupModel(const string& path);

protected:
	shared_ptr<Model> m_Model;
	vector<GLuint> m_VAOList;
	vector<Mesh> m_meshList;
	vector<shared_ptr<Material>> m_materialList;
};

