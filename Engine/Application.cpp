#define GLEW_STATIC
#include <iostream>
#include "BaseManager.h"



int main()
{
	BaseManager::getInstance()->run();
	return 0;
}
