#pragma once

#include "Vector3.h"

#include <vector>

namespace Ceres
{
    /// Wrapper around std::vector that has some helpful behavior
    class VertexList
    {
        public:
            VertexList();
            VertexList(int size);
            VertexList(std::initializer_list<Vector3>& init);
            VertexList(std::initializer_list<Vector3> init, std::allocator<Vector3> allocator);
            ~VertexList();

            Vector3& operator[](int index);
            const Vector3& operator[](int index) const;

            // iterator functions
            Vector3* begin() { return &_internalList[0]; }
            const Vector3* begin() const { return &_internalList[0]; }
            Vector3* end() { return &_internalList[Size()]; }
            const Vector3* end() const { return &_internalList[Size()]; }

            void Append(Vector3& vector);
            void Append(VertexList& vertexList);
            bool Contains(Vector3& vector);
            void Clear();
            void Insert(int index, Vector3& vector);
            bool RemoveAt(int index);
            void Reverse();
            int Size() const;

            std::string ToString() const;

        private:
            std::vector<Vector3> _internalList;
    };
}