#pragma once
#include "Ref.h"
#include "func.h"
#include "bulletHead.h"
class Rigidbody : public Ref
{
public:
	CREATE_FUNC(Rigidbody);
	virtual bool init();
	
};

