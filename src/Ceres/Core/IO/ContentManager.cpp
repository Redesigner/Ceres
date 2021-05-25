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
        fmt::print("Loading file '{}'...\n", currentPath.string());
        
        std::string file_content;
        std::getline(std::ifstream(currentPath), file_content, '\0');
        return file_content;
    }
}