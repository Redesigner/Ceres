#include "ContentManager.h"

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <fmt/core.h>

#include <algorithm>
#include <cmath>
#include <regex>

const std::string CWD = SDL_GetBasePath();
const std::string CONTENT_DIR = CWD + "..\\..\\content\\";

const std::string DEBUG_PREFIX = "[content]";
const std::string FILESIZE_SUFFIX[] = {"B", "kB", "mB", "gB"};

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

        float size = result.length();
        int i = 0;
        for (; i < sizeof(FILESIZE_SUFFIX) && size > 1000.0f; i++)
        {
            size = std::round(size) / 1000.0f;
        }
        fmt::print("{} loaded file '{}' successfully | {} {}\n", DEBUG_PREFIX, filename, size, FILESIZE_SUFFIX[i]);
        return result;
    }

    const MeshPrimitive<VertexPositionNormalTexture> ContentManager::LoadMesh(const char* filename)
    {
        std::string fileRaw = LoadString(filename);
        std::string::iterator lineStart = fileRaw.begin();
        std::string::iterator lineEnd = lineStart;
        const char newLine = '\n';

        std::vector<Vector3> points = std::vector<Vector3>();
        std::vector<Vector3> normals = std::vector<Vector3>();
        std::vector<Vector2> uV = std::vector<Vector2>();

        std::vector<VertexPositionNormalTexture> vertices = std::vector<VertexPositionNormalTexture>();
        std::vector<int> indices = std::vector<int>();

        while(lineEnd < fileRaw.end() && lineStart < fileRaw.end())
        {
            lineEnd = std::find(lineStart, fileRaw.end(), newLine);
            switch (*lineStart)
            {
                case '#':
                {
                    break;
                }
                case 'v':
                {
                    switch (*(lineStart + 1))
                    {
                        case ' ':
                        {
                            points.emplace_back(generateVertex(lineStart, lineEnd + 1));
                            break;
                        }
                        case 'n':
                        {
                            normals.emplace_back(generateVertex(lineStart, lineEnd + 1));
                            break;
                        }
                        case 't':
                        {
                            Vector3 vertex = generateVertex(lineStart, lineEnd + 1);
                            uV.emplace_back(vertex.X, vertex.Y);
                        }
                    }
                    break;
                }
                case 'f':
                {
                    addFace(lineStart, lineEnd + 1, points, normals, uV, vertices, indices);
                }
            }
            lineStart = lineEnd + 1;
        }
        return MeshPrimitive<VertexPositionNormalTexture>(vertices, indices);
    }

    Vector3 ContentManager::generateVertex(std::string::iterator& start, std::string::iterator& end)
    {
        Vector3 vertex;
        const std::regex separator("(?!\\s)[0-9|.|-]+?(?=\\s)");
        std::sregex_iterator iter(start, end, separator);
        std::sregex_iterator endRX;
        for (int i = 0; i < 3 && iter != endRX; i++)
        {
            float value = std::stof(iter->str());
            ++iter;
            switch (i)
            {
            case 0:
                vertex.X = value;
                break;
            case 1:
                vertex.Y = value;
                break;
            case 2:
                vertex.Z = value;
                break;
            }
        }
        return vertex;
    }

    void ContentManager::addFace(std::string::iterator& dataStart, std::string::iterator& dataEnd, const std::vector<Vector3> &vertices, const std::vector<Vector3> &normals, const std::vector<Vector2> &uvs, std::vector<VertexPositionNormalTexture>& mesh, std::vector<int>& indices)
    {
        const std::regex separator("(?!\\s)[0-9|/]+?(?=\\s)");
        std::sregex_iterator iter(dataStart, dataEnd, separator);
        std::sregex_iterator end;
        
        int vertexCount = 0;
        while (iter != end)
        {
            std::string vertexData = iter->str();
            ++iter;
            ++vertexCount;
            int vertex = 0;
            int normal = 0;
            int uv = 0;
            const std::regex subSeparator("(\\d+)(,\\s*\\d+)*");
            std::sregex_iterator subIter(vertexData.begin(), vertexData.end(), subSeparator);
            for (int j = 0; j < 3 && subIter != end; j++)
            {
                int value = std::stoi(subIter->str()) - 1;
                switch (j)
                {
                case 0:
                    vertex = value;
                    break;
                case 1:
                    uv = value;
                    break;
                case 2:
                    normal = value;
                    break;
                }
                ++subIter;
            }
            mesh.emplace_back(vertices[vertex], normals[normal], uvs[uv]);
        }
        int currentIndex = indices.size();
        int currentVertex = mesh.size();
        // Convert from triangle fan to triangle list
        for (int i = 0; i < vertexCount - 2; i++)
        {
            int a = currentVertex - vertexCount;
            int b = a + i + 1;
            int c = a + i + 2;
            indices.insert(indices.end(), {a, b, c});
        }
    }
}