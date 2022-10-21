#include "ModelEntity.h"
#include "Model.h"
#include "MaterialManager.h"
#include "ModelNode.h"
#include "Mesh.h"
bool ModelEntity::init()
{
    if (!Node::init())
        return false;
    nodeType = NodeType::Normal;
    return true;
}

void ModelEntity::draw()
{
}

void ModelEntity::setupModel(const string& path)
{
    m_Model = std::make_shared<Model>(Model(MODEL_PATH + path, false));
    for (int i = 0; i < m_Model->meshes.size(); i++)
    {
        ModelNode* modelNode = ModelNode::create(MaterialType::PBR);
        modelNode->setMeshAndBuffer(m_Model->meshes[i]);
        this->addChild(modelNode);
    }
}
