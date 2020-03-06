#include "Component.h"

void Component::use()
{
}

Component::Component() : tag("")
{
}

Component::~Component()
{
	setEntity(nullptr);
}
bool Component::operator==(Component& com)
{
	return com.getComTypeI() == this->getComTypeI() && com.getComTypeII() == this->getComTypeII();
}
bool Component::init()
{
	return true;
}
