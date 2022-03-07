#pragma once

#include "../Graphics/VertexTypes/VertexPositionNormalTexture.h"
#include "../Graphics/Primitives/MeshPrimitive.h"

#include <string>
#include <vector>

namespace Ceres
{
    class ContentManager
    {
        public:
            ContentManager();
            ~ContentManager();
            static const std::string LoadString(const char* filename);
            static const MeshPrimitive<VertexPositionNormalTexture> LoadMesh(const char* filename);
        private:
            static Vector3 generateVertex(std::string::iterator& start, std::string::iterator& end);
            static void addFace(std::string::iterator& start, std::string::iterator& end, const std::vector<Vector3> &vertices, const std::vector<Vector3> &normals, const std::vector<Vector2> &uvs, std::vector<VertexPositionNormalTexture>& mesh, std::vector<int>& indices);
    };
}