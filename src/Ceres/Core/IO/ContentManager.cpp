#include "ContentManager.h"

#include <filesystem>
#include <fstream>
#include <string>

#include <fmt/core.h>

namespace fs = std::filesystem;
const char* CONTENTPATH = "Content";

// TODO: Make this whole class not suck :)
namespace Ceres
{
    const std::string ContentManager::LoadString(const char* filename)
    {
        fs::path currentPath = fs::current_path();
        currentPath.append(CONTENTPATH);
        currentPath.append(filename);
        fmt::print("Loading file: '{}'...\n", currentPath.string());
        
        std::ifstream ifs (currentPath, std::ifstream::in);
        std::string file_content;
        ifs.seekg(0, std::ios::end);
        file_content.resize(ifs.tellg());
        ifs.seekg(0, std::ios::beg);
        ifs.read(&file_content[0], file_content.size());
        ifs.close();

        fmt::print("File loaded successfully, length: {}\n", file_content.length());
        return file_content;
    }
}