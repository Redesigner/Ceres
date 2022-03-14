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
            const std::string LoadString(const char* filename) const;
            const MeshPrimitive<VertexPositionNormalTexture> LoadMesh(const char* filename) const;
        private:
            Vector3 generateVertex(std::string::iterator& start, std::string::iterator& end) const;
            
            void addFace(std::string::iterator& start, std::string::iterator& end,
                const std::vector<Vector3> &vertices, const std::vector<Vector3> &normals, const std::vector<Vector2> &uvs,
                std::vector<VertexPositionNormalTexture>& mesh, std::vector<int>& indices) const;
    };
}