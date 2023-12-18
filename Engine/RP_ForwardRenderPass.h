#pragma once
#include "RP_RenderPass.h"
class RP_ForwardRenderPass :
    public RP_RenderPass
{
public:
    bool Init() override;
    bool Render() override;
    ~RP_ForwardRenderPass() override;
};


