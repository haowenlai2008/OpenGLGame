#pragma once
#include "Wheel.h"
class LeftWheel :
	public Wheel
{
public:
	CREATE_FUNC(LeftWheel);
	virtual bool init() override;
};

