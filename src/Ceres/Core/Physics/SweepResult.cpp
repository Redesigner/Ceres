#include "SweepResult.h"

namespace Ceres
{
    SweepResult::SweepResult(bool result, Vector3 collisionNormal, float distance)
        :_result(result), _collisionNormal(collisionNormal), _distance(distance)
    {}

    SweepResult::SweepResult(bool result)
        :_result(result), _collisionNormal(Vector3::Zero()), _distance(0.0f)
    {}

    bool SweepResult::Hit() const
    {
        return _result;
    }

    Vector3 SweepResult::GetNormal() const
    {
        return _result ? _collisionNormal : Vector3::Zero();
    }

    float SweepResult::GetDistance() const
    {
        return _result ? _distance : 0.0f;
    }

    Vector3 SweepResult::GetDelta() const
    {
        return _result ? -1.0f * _collisionNormal * _distance : Vector3::Zero();
    }
}