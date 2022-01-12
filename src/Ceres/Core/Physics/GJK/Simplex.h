#pragma once

#include "../../Common/Vector3.h"
#include "../../Common/VertexList.h"

#include <vector>
#include <string>

using uint = unsigned int;

namespace Ceres
{
    class Simplex
    {
        public:
            Simplex();
            ~Simplex();

            bool SafeAdd(Vector3 vertex);
            bool SafeAddList(VertexList vertices);

            const Vector3 GetVertex(uint a) const;

            Vector3 GetNormal(uint a, uint b, uint c);
            Vector3 GetNormal(uint a, uint b, Vector3 origin);
            Vector3 GetNextNormal();

            Vector3 GetTriangleNormal(uint a, uint b, uint c);
            Vector3 NormalAwayFromPoint(uint a, uint b, uint c, Vector3 point);
            Vector3 NormalAwayFromPoint(uint a, uint b, uint c, uint d);
            
            VertexList GetPrimaryNormals();
            Vector3 CullNoncontributingVertices(Vector3 point);
            Vector3 GetShortestDistance(Vector3 point);
            bool CollapseVornoiRegions(Vector3 point);

            bool IsFull();
            bool ContainsPoint(Vector3 point);
            bool FaceContainsPoint(uint a, uint b, uint c, Vector3 point);

            uint GetVertexCount() { return _vertexCount; }
            std::string ToString() const;

        private:
            void insertVertex(uint index, Vector3 vertex);
            void removeVertex(uint index);
            void addVertex(Vector3 vertex);
            bool containsVertex(Vector3 vertex);
            bool deletedContains(Vector3 vertex);
            void removeLast();

            void storeNormalsInCache(VertexList normals);
            VertexList getCachedNormals();

            bool isCoplanar(Vector3 point);
            bool isColinear(Vector3 point);

            uint _vertexCount;
            VertexList _vertices;
            Vector3 _lastRemovedVertex;

            bool _regenNormalsFlag;
            bool _regenNextNormalFlag;

            VertexList _cachedNormals;
            Vector3 _cachedNextNormal;
            VertexList _deletedVertices;
    };
}