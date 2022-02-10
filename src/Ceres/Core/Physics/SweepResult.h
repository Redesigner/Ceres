#pragma once

#include "../Common/Vector3.h"

namespace Ceres
{
    struct SweepResult
    {
        public:
            SweepResult(bool result, Vector3 collisionNormal, float distance);
            SweepResult(bool result);

            bool Hit() const;
            Vector3 GetNormal() const;
            float GetDistance() const;
            Vector3 GetDelta() const;

        private:
            const bool _result;
            const Vector3 _collisionNormal;
            const float _distance;
    };
}