#include "opengl_game/core/ResourceLocator.h"

#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

namespace
{
std::filesystem::path executableDirectory()
{
#ifdef _WIN32
    std::wstring buffer(32768, L'\0');
    const DWORD length = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
    if (length != 0 && length < buffer.size()) {
        buffer.resize(length);
        return std::filesystem::path(buffer).parent_path();
    }
#endif
    return std::filesystem::current_path();
}
}

std::filesystem::path ResourceLocator::root()
{
    if (const char* configured = std::getenv("OPENGLGAME_RESOURCE_DIR")) {
        if (*configured != '\0') {
            return std::filesystem::path(configured);
        }
    }
    return executableDirectory() / "Resources";
}

std::string ResourceLocator::directory(const std::filesystem::path& relative)
{
    auto value = (root() / relative).generic_string();
    if (value.empty() || value.back() != '/') {
        value.push_back('/');
    }
    return value;
}

std::string ResourceLocator::file(const std::filesystem::path& relative)
{
    return (root() / relative).generic_string();
}
