#pragma once
#include "opengl_game/render/RP_RenderPass.h"
class RP_ToneMappingGammaPass :
    public RP_RenderPass
{
public:
    bool Init() override;
    bool Render() override;
    bool Release() override;
};

