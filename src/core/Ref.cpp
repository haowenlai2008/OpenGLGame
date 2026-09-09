#include "Ref.h"
#include "RefManager.h"
#include <iostream>


Ref::Ref() : count(0)
{
}


Ref::~Ref()
{
}

void Ref::retain()
{
	count += 1;
}

void Ref::release()
{
	count > 0 ? count-- : count = 0;
}

void Ref::autorelease()
{
	RefManager::getInstance()->addRef(this);
}
