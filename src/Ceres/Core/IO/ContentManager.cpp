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
        while (ifs.good())
        {
            file_content += (char) (ifs.get());
        }
        ifs.close();
        fmt::print("File loaded successfully, length: {}\n", file_content.length());
        return file_content;
    }
}