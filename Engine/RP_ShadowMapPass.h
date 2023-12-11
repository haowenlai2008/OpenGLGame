#pragma once
#include "RP_RenderPass.h"
class RP_ShadowMapPass :
    public RP_RenderPass
{
public:
    bool Init() override;
    bool Render() override;
};

