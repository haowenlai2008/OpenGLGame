#pragma once
#include "RP_RenderPass.h"
class RP_ScenePass :
    public RP_RenderPass
{
public:
    bool Init() override;
    bool Render() override;
};

