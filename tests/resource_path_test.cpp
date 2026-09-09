#include <filesystem>
#include <cstdlib>
#include <iostream>

#include "ResourceLocator.h"

int main()
{
    const std::filesystem::path configuredRoot{"C:/OpenGLGameTestResources"};
#ifdef _WIN32
    _putenv_s("OPENGLGAME_RESOURCE_DIR", configuredRoot.string().c_str());
#else
    setenv("OPENGLGAME_RESOURCE_DIR", configuredRoot.string().c_str(), 1);
#endif
    if (ResourceLocator::root() != configuredRoot) {
        std::cerr << "Resource locator ignored OPENGLGAME_RESOURCE_DIR\n";
        return 1;
    }
    return 0;
}
