#include "GJK.h"

#include "../PhysicsUtilities.h"

#include <fmt/core.h>

namespace Ceres
{
    GJK::GJK(PhysicsComponent* shapeA, PhysicsComponent* shapeB)
        : _shapeA(shapeA), _shapeB(shapeB)
    {
        GenerateMinkowskiDifference();
    }

    GJK::~GJK()
    {}

    GJK::CollisionType GJK::Solve(Vector3* outDistance, Vector3* outDirection)
    {
        *outDistance = Vector3::Zero();
        *outDirection = Vector3::Zero();
        for (int i = 0; i < maxIterations; i++)
        {
            fmt::print("{}\n\n", MinkowskiDifference.ToString());
            if (MinkowskiDifference.IsFull())
            {
                if (MinkowskiDifference.ContainsPoint(Vector3::Zero()))
                {
                    fmt::print("{}\n\n", MinkowskiDifference.ToString());
                    return Penetration;
                }
                MinkowskiDifference.CullNoncontributingVertices(Vector3::Zero());
            }
            else
            {
                searchDirection = MinkowskiDifference.GetNextNormal();
                VertexList nextPoints = PhysicsUtilities::SupportPoints(*_shapeA->GetPrimitive(), *_shapeB->GetPrimitive(), searchDirection);
                if (!MinkowskiDifference.SafeAddList(nextPoints) && !MinkowskiDifference.CollapseVornoiRegions(Vector3::Zero()))
                {
                    *outDistance = MinkowskiDifference.GetShortestDistance(Vector3::Zero());
                    *outDirection = MinkowskiDifference.GetNextNormal();
                    fmt::print("{}\n\n", MinkowskiDifference.ToString());
                    return static_cast<GJK::CollisionType>(MinkowskiDifference.GetVertexCount());
                }
            }
        }
        return None;
    }

    void GJK::GenerateMinkowskiDifference()
    {
        MinkowskiDifference = Simplex();
        Vector3 searchDirection = (_shapeB->GetPosition() - _shapeA->GetPosition()).Normalize();
        if (PhysicsUtilities::NearlyZero(searchDirection))
        {
            searchDirection = Vector3::Up();
        }
        VertexList newPoints = PhysicsUtilities::GiftWrap(PhysicsUtilities::SupportPoints(*_shapeA->GetPrimitive(), *_shapeB->GetPrimitive(), searchDirection));
        MinkowskiDifference.SafeAdd(newPoints[0]);
    }
}