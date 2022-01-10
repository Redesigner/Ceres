#pragma once

#include "../../Common/Vector3.h"
#include "../../Components/PhysicsComponent.h"
#include "Simplex.h"

namespace Ceres
{
    class GJK
    {
        public:
            enum CollisionType{None, Point, Line, Face, Penetration};

            GJK(PhysicsComponent* shapeA, PhysicsComponent* shapeB);
            ~GJK();

            void GenerateMinkowskiDifference();
            CollisionType Solve(Vector3* outDistance, Vector3* outDirection);

            Simplex MinkowskiDifference;

        private:
            const int maxIterations = 16;

            Vector3 searchDirection;
            PhysicsComponent* _shapeA;
            PhysicsComponent* _shapeB;
    };
}