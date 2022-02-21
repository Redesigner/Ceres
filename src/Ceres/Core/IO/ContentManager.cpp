#include "ContentManager.h"

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <fmt/core.h>

const std::string CWD = SDL_GetBasePath();
const std::string CONTENT_DIR = CWD + "..\\..\\content\\";

const std::string DEBUG_PREFIX = "[content]";

// TODO: Make this whole class not suck :)
// ...and use SDL functions instead of windows specific ones
namespace Ceres
{
    const std::string ContentManager::LoadString(const char* filename)
    {
        std::string currentPath = CONTENT_DIR;
        currentPath.append(filename);
        SDL_RWops* sdlRW = SDL_RWFromFile(currentPath.c_str(), "r");
        if (!sdlRW)
        {
            return std::string("");
        }
        sdlRW = SDL_RWFromFile(currentPath.c_str(), "r");
        std::string result = std::string();

        char out = 0;
        while (SDL_RWread(sdlRW, &out, 1, 1) != 0)
        {
            result.insert(result.end(), out);
        }
        SDL_RWclose(sdlRW);

        fmt::print("{} loaded file '{}' successfully | {}B\n", DEBUG_PREFIX, filename, result.length());
        return result;
    }
}