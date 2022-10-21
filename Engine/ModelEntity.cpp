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
    Model model = Model(MODEL_PATH + path);
    for (int i = 0; i < model.meshes.size(); i++)
    {
        auto& sysMaterial = MaterialManager::getInstance()->getSystemMaterial(MaterialType::ModelPBR);
        ModelNode* modelNode = ModelNode::create(MaterialType::PBR);
        modelNode->setMeshAndBuffer(model.meshes[i]);
        modelNode->setTexture("container.jpg");
        this->addChild(modelNode);
    }
}
