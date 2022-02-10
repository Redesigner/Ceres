#include "VertexList.h"

#include <cstdarg>

#include <cstdio>

namespace Ceres
{
    VertexList::VertexList()
        :_internalList()
    {}

    VertexList::VertexList(const VertexList& Other)
        : _internalList(Other._internalList)
    {}

    VertexList::VertexList(int size)
        :_internalList(size)
    {}

    VertexList::VertexList(std::initializer_list<Vector3> init)
        :_internalList(init)
    {}

    VertexList::VertexList(std::initializer_list<Vector3> init, std::allocator<Vector3> allocator)
        :_internalList(init, allocator)
    {}

    VertexList::~VertexList()
    {}

    Vector3& VertexList::operator[](int index)
    {
        return _internalList[index];
    }

    const Vector3& VertexList::operator[](int index) const
    {
        return _internalList[index];
    }

    Vector3* VertexList::begin()
    {
        if (Size() == 0) { return nullptr; }
        return _internalList.data();
    }
    const Vector3* VertexList::begin() const
    {
        if (Size() == 0) { return nullptr; }
        return _internalList.data();
    }
    Vector3* VertexList::end()
    {
        if (Size() == 0) { return nullptr; }
        return _internalList.data() + Size();
    }
    const Vector3* VertexList::end() const
    {
        if (Size() == 0) { return nullptr; }
        return _internalList.data() + Size();
    }

    void VertexList::Append(Vector3& vertex)
    {
        _internalList.emplace_back(vertex);
    }

    void VertexList::Append(VertexList& vertexList)
    {
        _internalList.insert(_internalList.end(), vertexList.begin(), vertexList.end() );
    }

    bool VertexList::Contains(Vector3& vertex)
    {
        for (Vector3 internalVertex : _internalList)
        {
            if (internalVertex == vertex)
            {
                return true;
            }
        }
        return false;
    }

    void VertexList::Clear()
    {
        _internalList.clear();
    }

    void VertexList::Insert(int index, Vector3& vector)
    {
        _internalList.emplace(_internalList.begin() + index, vector);
    }

    bool VertexList::RemoveAt(int index)
    {
        if (Size() <= index) { return false; }
        _internalList.erase(_internalList.begin() + index);
        return true;
    }

    void VertexList::Reverse()
    {
        int size = Size() - 1;
        for (int i = 0; i < size / 2; i++)
        {
            Vector3 swap = _internalList[size - i];
            _internalList[size - i] = _internalList[i];
            _internalList[i] = swap;
        }
    }

    int VertexList::Size() const
    {
        return _internalList.size();
    }

    std::string VertexList::ToString() const
    {
        std::string values = "{";
        for (int i = 0; i < Size(); i++)
        {
            values.append(_internalList[i].ToString());
            if (i < Size() - 1)
            {
                values.append(", ");
            }
        }
        values.append("}");
        return values;
    }
}