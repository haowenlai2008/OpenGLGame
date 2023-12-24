#pragma once
#include "RP_RenderPass.h"
class RP_PostProcessPass :
    public RP_RenderPass
{
public:
    bool Init() override;
    bool Render() override;
    bool Release() override;
};

