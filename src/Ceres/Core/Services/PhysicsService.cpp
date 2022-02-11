#include "PhysicsService.h"

#include "../Components/PhysicsComponent.h"
#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/PhysicsUtilities.h"
#include "../Physics/GJK/GJK.h"
#include "../Physics/GJK/Simplex.h"

#include "RenderService.h"
#include "../Graphics/VertexTypes/VertexPosition.h"

#include <stdexcept>
#include <fmt/core.h>

#define KILL_Z -3.0f

namespace Ceres
{
    PhysicsService::PhysicsService()
    {}

    PhysicsService::PhysicsService(RenderService* debugRenderer)
        :_debugRenderer(debugRenderer)
    {}


    PhysicsService::~PhysicsService()
    {}


    ComponentRef PhysicsService::GenerateComponent(std::string typeName, const IEntity& parent, int argCount, void* args)
    {
        if (typeName == "PhysicsComponent")
        {
            if (argCount == 1)
            {
                IPrimitive* primitive = static_cast<IPrimitive*>(args);
                _components.Insert(new PhysicsComponent(parent, primitive));
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", typeName));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", typeName));
        }
    }


    void PhysicsService::Update(float deltaSeconds)
    {
        for (IComponent* component : _components)
        {
            PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(component);
            if (!physicsComponent)
            {
                continue;
            }
            stepComponent(physicsComponent, deltaSeconds);
        }
    }


    std::vector<PhysicsComponent*> PhysicsService::getComponentsWithinDistance(PhysicsComponent* sourceComponent, const float distance)
    {
        std::vector<PhysicsComponent*> result = std::vector<PhysicsComponent*>();
        for (IComponent* target : _components)
        {
            PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(target);
            if (!physicsComponent)
            {
                continue;
            }
            if (physicsComponent == sourceComponent)
            {
                continue;
            }

            float separation = (physicsComponent->GetPosition() - sourceComponent->GetPosition()).Length();
            float combinedWidth = physicsComponent->SemiMajorAxis() + sourceComponent->SemiMajorAxis() + distance;
            if (separation <= combinedWidth)
            {
                result.emplace_back(physicsComponent);
            }
        }
        return result;
    }

    void PhysicsService::stepComponent(PhysicsComponent* host, float seconds)
    {
        if (seconds <= 0.0f || (PhysicsUtilities::NearlyZero(host->Acceleration) && PhysicsUtilities::NearlyZero(host->Velocity)))
        {
            return;
        }
        host->Velocity += host->Acceleration * seconds;
        float semiMajorAxis = host->GetPrimitive()->SemiMajorAxis();
        float searchDistance = host->Velocity.LengthSquared() * seconds + semiMajorAxis * semiMajorAxis;

        Vector3 v = host->Velocity * seconds;
        Vector3 vN = v.Normalize();
        Vector3 delta = v;
        bool impact = false;

        GJK::CollisionType status = GJK::CollisionType::None;
        VertexList debug = VertexList();


        std::vector<PhysicsComponent*> targets = getComponentsWithinDistance(host, searchDistance);
        std::vector<SweepResult> collisions = std::vector<SweepResult>();
        for (PhysicsComponent* target : targets)
        {
            // Make sure we aren't sweeping against ourself
            if (host == target)
            {
                continue;
            }

            SweepResult sweep = PhysicsUtilities::Sweep(*host->GetPrimitive(), *target->GetPrimitive(), v + vN * Vector3::Epsilon(), &debug);
            // Collision found with sweep algorithm
            if (sweep.Hit())
            {
                if (!impact)
                {
                    // _debugRenderer->ClearWireframe();
                }
                impact = true;
                collisions.emplace_back(sweep);
            }
        }
        if (impact)
        {
            float vMag = delta.Length();
            for (SweepResult sweep : collisions)
            {
                if (sweep.Hit())
                {
                    delta -= (vMag - sweep.GetDistance() + Vector3::Epsilon()) * sweep.GetNormal() * sweep.GetNormal().Dot(vN);
                    host->Velocity -= host->Velocity.Dot(sweep.GetNormal()) * sweep.GetNormal();
                }
            }
            // _debugRenderer->LoadWireframeData(debug);
        }
        // Don't make veryy small moves. This should prevent sliding
        /* if (delta.LengthSquared() < Vector3::Epsilon())
        {
            return;
        } */
        Vector3 newPosition = host->GetPosition() + delta;
        if (newPosition.Z <= KILL_Z)
        {
            newPosition.Z = KILL_Z;
            host->Velocity.Z = 0.0f;
        }
        host->SetPosition(newPosition);
    }
}