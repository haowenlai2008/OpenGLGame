#pragma once

class RP_RenderPass
{
public:
	virtual bool Init() = 0;
	virtual bool Render() = 0;
};

