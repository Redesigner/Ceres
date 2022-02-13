#pragma once

#include "../Common/Vector3.h"

namespace Ceres
{
    struct SweepResult
    {
        public:
            SweepResult(bool result, Vector3 collisionNormal, float distance, bool penetrating);
            SweepResult(bool result, Vector3 collisionNormal, float distance);
            SweepResult(bool result);

            bool Hit() const;
            Vector3 GetNormal() const;
            float GetDistance() const;
            bool Penetrating() const;
            Vector3 GetDelta() const;

        private:
            bool _result;
            bool _penetrating;
            Vector3 _collisionNormal;
            float _distance;
    };
}