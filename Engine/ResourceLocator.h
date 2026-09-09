#pragma once

#include <filesystem>
#include <string>

class ResourceLocator
{
public:
    static std::filesystem::path root();
    static std::string directory(const std::filesystem::path& relative);
    static std::string file(const std::filesystem::path& relative);
};
