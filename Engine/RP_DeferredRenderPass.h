#pragma once
#include "RP_RenderPass.h"
class RP_DeferredRenderPass :
    public RP_RenderPass
{
public:
    bool Init() override;
    bool Render() override;
    bool Release() override;
};

