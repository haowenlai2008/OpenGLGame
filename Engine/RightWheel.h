#pragma once
#include "Wheel.h"
class RightWheel :
	public Wheel
{
public:
	CREATE_FUNC(RightWheel);
	virtual bool init() override;
};

