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
    auto model = Model(MODEL_PATH + path);
    for (int i = 0; i < model.meshes.size(); i++)
    {
        ModelNode* modelNode = ModelNode::create(MaterialType::PBR);
        modelNode->setMeshAndBuffer(model.meshes[i]);
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < model.textures_loaded.size(); i++)
        {
            string number;
            string name = model.textures_loaded[i].m_type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream
        }
        
        this->addChild(modelNode);
    }
}
