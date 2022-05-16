#include "ModelEntity.h"
#include "Model.h"
bool ModelEntity::init()
{
    if (!Entity::init())
        return false;

    return true;
}

void ModelEntity::setupModel(const string& path)
{

}
