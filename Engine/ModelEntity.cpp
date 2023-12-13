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
        ModelNode* modelNode = ModelNode::create("IBL_PBR");
        modelNode->setMeshAndBuffer(model.meshes[i]);
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        cout << "Model:" + path + " Mesh num = " << i << endl;
        for (unsigned int j = 0; j < model.meshes[i].textures.size(); j++)
        {
            string number;
            string name = model.meshes[i].textures[j].m_type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            cout << name + number + " = " << model.meshes[i].textures[j].m_path << endl;
            if (name == "texture_diffuse" && number == "1")
            {
                auto mat =  modelNode->GetMaterial().lock();
                mat->setTexture("material.diffuse", model.meshes[i].textures[j], 0);
                //mat->setTexture("material.diffuse", "container2.png", 0, TextureType::Texture2D);
            }
        }
        this->addChild(modelNode);
    }
}
