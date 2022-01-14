#include "Simplex.h"

#include "../PhysicsUtilities.h"
#include <fmt/core.h>

namespace Ceres
{
    Simplex::Simplex()
    {
        _vertexCount = 0;
        _vertices = VertexList();
        _deletedVertices = VertexList();
        _regenNormalsFlag = true;
        _regenNextNormalFlag = true;
    }

    Simplex::~Simplex()
    {}


    const Vector3 Simplex::GetVertex(uint a) const
    {
        if(_vertexCount > a)
        {
            return _vertices[a];
        }
        return Vector3::Zero();
    }

    std::string Simplex::ToString() const
    {
        return fmt::format("Simplex [{}]: {}", _vertexCount, _vertices.ToString());
    }

    void Simplex::insertVertex(uint index, Vector3 vertex)
    {
        _regenNormalsFlag = true;
        _regenNextNormalFlag = true;
        if (_vertexCount >= 4)
        {
            removeLast();
        }

        _vertices.Insert(index, vertex);
        if (_vertexCount < 4)
        {
            _vertexCount++;
        }
    }

    void Simplex::removeVertex(uint index)
    {
        _regenNormalsFlag = true;
        _regenNextNormalFlag = true;
        _lastRemovedVertex = _vertices[index];
        _deletedVertices.Append(_lastRemovedVertex);
        _vertices.RemoveAt(index);
        _vertexCount--;
    }

    void Simplex::addVertex(Vector3 vertex)
    {
        insertVertex(0, vertex);
    }

    bool Simplex::containsVertex(Vector3 vertex)
    {
        for (Vector3 shapeVertex : _vertices)
        {
            if (PhysicsUtilities::NearlyZero(vertex - shapeVertex))
            {
                return true;
            }
        }
        return false;
    }


    bool Simplex::deletedContains(Vector3 vertex)
    {
        for (Vector3 shapeVertex : _deletedVertices)
        {
            if (PhysicsUtilities::NearlyZero(vertex - shapeVertex))
            {
                return true;
            }
        }
        return false;
    }


    bool Simplex::SafeAdd(Vector3 vertex)
    {
        if (_lastRemovedVertex == vertex) { return false; }
        if (containsVertex(vertex)) { return false; }
        if (deletedContains(vertex)) { return false; };
        if (isCoplanar(vertex)) { return false; }
        if (isColinear(vertex)) { return false; }

        addVertex(vertex);
        return true;
    }

    bool Simplex::SafeAddList(VertexList vertices)
    {
        for (Vector3 vertex : vertices)
        {
            if (SafeAdd(vertex))
            {
                return true;
            }
        }
        return false;
    }

    void Simplex::removeLast()
    {
        removeVertex(_vertexCount - 1);
    }

    Vector3 Simplex::GetNormal(uint a, uint b, uint c)
    {
        if (a >= _vertexCount || b >= _vertexCount || c > _vertexCount)
        {
            throw std::exception("The specified index for the point is invalid.");
        }
        return PhysicsUtilities::GetNormal(_vertices[a], _vertices[b], _vertices[c]);
    }

    Vector3 Simplex::GetNormal(uint a, uint b, Vector3 origin)
    {
        if (a >= _vertexCount || b >= _vertexCount)
        {
            throw std::exception("The specified index for the point is invalid.");
        }
        return ((_vertices[b] - _vertices[a]).Triple(origin - _vertices[a])).Normalize();
    }

    Vector3 Simplex::GetTriangleNormal(uint a, uint b, uint c)
    {
        if (a >= _vertexCount || b >= _vertexCount || c > _vertexCount)
        {
            throw std::exception("The specified index for the point is invalid.");
        }
        return -1 * (_vertices[b] - _vertices[a]).Triple(_vertices[c] - _vertices[a]).Normalize();
    }

    Vector3 Simplex::NormalAwayFromPoint(uint a, uint b, uint c, Vector3 point)
    {
        if (a >= _vertexCount || b >= _vertexCount || c > _vertexCount)
        {
            throw std::exception("The specified index for the point is invalid.");
        }
        Vector3 normal = GetNormal(a, b, c);
        float dot = normal.Dot(point - _vertices[a]);
        return dot < 0 ? normal : -1 * normal;
    }

    Vector3 Simplex::NormalAwayFromPoint(uint a, uint b, uint c, uint d)
    {
        if (a >= _vertexCount || b >= _vertexCount || c > _vertexCount)
        {
            throw std::exception("The specified index for the point is invalid.");
        }
        return NormalAwayFromPoint(a, b, c, _vertices[d]);
    }

    bool Simplex::IsFull()
    {
        return _vertexCount == 4;
    }

    void Simplex::storeNormalsInCache(VertexList normals)
    {
        _regenNormalsFlag = false;
        _cachedNormals = normals;
    }

    VertexList Simplex::getCachedNormals()
    {
        return _cachedNormals;
    }

    Vector3 Simplex::GetNextNormal()
    {
        if (!_regenNextNormalFlag)
        {
            return _cachedNextNormal;
        }
        switch (_vertexCount)
        {
            case 1:
                {
                    _cachedNextNormal = -1 * _vertices[0].Normalize();
                    _regenNextNormalFlag = false;
                    return _cachedNextNormal;
                }
            case 2:
                {
                    _cachedNextNormal = GetNormal(0, 1, Vector3::Zero());
                    _regenNextNormalFlag = false;
                    return _cachedNextNormal;
                }
            case 3:
                {
                    _cachedNextNormal = -1 * NormalAwayFromPoint(0, 1, 2, Vector3::Zero());
                    _regenNextNormalFlag = false;
                    return _cachedNextNormal;
                }
            case 4:
                {
                    _cachedNextNormal = -1 * NormalAwayFromPoint(0, 1, 2, Vector3::Zero());
                    _regenNextNormalFlag = false;
                    return _cachedNextNormal;
                }
            default:
                return Vector3::Zero();
        }
    }

    VertexList Simplex::GetPrimaryNormals()
    {
        if (!_regenNormalsFlag)
        {
            return getCachedNormals();
        }
        switch (_vertexCount)
        {
            case 1:
                {
                    VertexList result = VertexList(1);
                    result[0] = -1 * _vertices[0].Normalize();
                    storeNormalsInCache(result);
                    return result;
                }
            case 2:
                {
                    VertexList result = VertexList(2);
                    result[0] = (_vertices[0] - _vertices[1]).Normalize();
                    result[1] = -1 * result[0];
                    storeNormalsInCache(result);
                    return result;
                }
            case 3:
                {
                    VertexList result = VertexList(3);
                    result[0] = GetTriangleNormal(0, 1, 2);
                    result[1] = GetTriangleNormal(1, 2, 0);
                    result[2] = GetTriangleNormal(2, 0, 1);
                    storeNormalsInCache(result);
                    return result;
                }
            case 4:
                {
                    VertexList result = VertexList(4);
                    result[0] = NormalAwayFromPoint(0, 1, 2, 3);
                    result[1] = NormalAwayFromPoint(1, 2, 3, 0);
                    result[2] = NormalAwayFromPoint(2, 3, 0, 1);
                    result[3] = NormalAwayFromPoint(3, 0, 1, 2);
                    storeNormalsInCache(result);
                    return result;
                }
            default:
                return VertexList();
        }
    }

    Vector3 Simplex::CullNoncontributingVertices(Vector3 point)
    {
        if (_vertexCount == 4)
        {
            VertexList normals = GetPrimaryNormals();
            int culledVertexI = 3;
            float maxDistance = normals[0].Dot(_vertices[0]);
            Vector3 longestNormal = normals[0];
            for (int i = 1; i < normals.Size(); i++)
            {
                double distanceFromNormal = normals[i].Dot(_vertices[i] - point);
                if (distanceFromNormal < maxDistance)
                {
                    maxDistance = distanceFromNormal;
                    culledVertexI = i - 1;
                    longestNormal = normals[i];
                }
            }
            removeVertex(culledVertexI);
            return longestNormal;
        }
        return Vector3::Zero();
    }

    Vector3 Simplex::GetShortestDistance(Vector3 point)
    {
        if (_vertexCount == 0) { return Vector3::Zero(); }
        Vector3 shortestNormal = GetNextNormal();
        return shortestNormal * shortestNormal.Dot(point - _vertices[0]);
    }

    bool Simplex::CollapseVornoiRegions(Vector3 point)
    {
        switch (_vertexCount)
        {
            case 2:
                {
                    VertexList normals = GetPrimaryNormals();
                    VertexList oldVertices = VertexList(_vertices);
                    if (normals[0].Dot(point - _vertices[0]) >= 0)
                    {
                        removeVertex(1);
                        return true;
                    }
                    if (normals[1].Dot(point - oldVertices[1]) >= 0)
                    {
                        removeVertex(0);
                        return true;
                    }
                    return false;
                }
            case 3:
                {
                    bool collapsed = false;
                    VertexList normals = GetPrimaryNormals();
                    VertexList oldVertices = VertexList(_vertices);
                    float dot1 = normals[0].Dot(point - oldVertices[0]);
                    float dot2 = normals[2].Dot(point - oldVertices[2]);
                    float dot3 = normals[1].Dot(point - oldVertices[1]);
                    if (dot1 > 0 && PhysicsUtilities::PointBetween(oldVertices[0], oldVertices[1], point))
                    {
                        removeVertex(2);
                        collapsed = true;
                    }
                    if (dot2 > 0 && PhysicsUtilities::PointBetween(oldVertices[0], oldVertices[2], point))
                    {
                        removeVertex(1);
                        collapsed = true;
                    }
                    if (dot3 > 0 && PhysicsUtilities::PointBetween(oldVertices[1], oldVertices[2], point))
                    {
                        removeVertex(0);
                        collapsed = true;
                    }
                    if (collapsed) { return true; }
                    else
                    {
                        if (dot1 > dot2 && dot1 > dot3 && dot1 > 0)
                        {
                            removeVertex(2);
                            return true;
                        }
                        if (dot2 > dot1 && dot2 > dot3 && dot2 > 0)
                        {
                            removeVertex(1);
                            return true;
                        }
                        if (dot3 > dot1 && dot3 > dot2 && dot3 > 0)
                        {
                            removeVertex(0);
                            return true;
                        }
                    }
                    return false;
                }
            default:
                {
                    return false;
                }
        }
    }

    bool Simplex::isCoplanar(Vector3 point)
    {
        if (_vertexCount != 3) { return false; }
        Vector3 normal = GetNextNormal();
        float difference = _vertices[0].Dot(normal) - point.Dot(normal);
        return PhysicsUtilities::NearlyZero(difference);
    }

    bool Simplex::isColinear(Vector3 point)
    {
        if (_vertexCount != 2) { return false; }
        return PhysicsUtilities::Colinear(_vertices[0], _vertices[1], point);
    }

    bool Simplex::ContainsPoint(Vector3 point)
    {
        if (!IsFull()) { return false; }
        VertexList normals = GetPrimaryNormals();
        for (int i = 0; i < normals.Size(); i++)
        {
            Vector3 vertexInNormal = _vertices[i];
            if (normals[i].Dot(point - vertexInNormal) > Vector3::Epsilon())
            {
                return false;
            }
        }
        return true;
    }

    bool Simplex::FaceContainsPoint(uint a, uint b, uint c, Vector3 point)
    {
        if (_vertexCount < 3)
        {
            return false;
        }
        VertexList normals = VertexList(3);
        normals[0] = GetTriangleNormal(a, b, c);
        normals[1] = GetTriangleNormal(b, c, a);
        normals[2] = GetTriangleNormal(c, a, b);
        return
           (normals[0].Dot(point - _vertices[c]) > 0)
        && (normals[1].Dot(point - _vertices[a]) > 0)
        && (normals[2].Dot(point - _vertices[b]) > 0);
    }
}