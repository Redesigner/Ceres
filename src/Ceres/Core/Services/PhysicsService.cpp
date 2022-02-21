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

#define MAX_SUBSTEPS 4
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


    ComponentRef PhysicsService::GenerateComponent(std::string type, const IEntity& parent, ComponentParams* params)
    {
        if (type == "PhysicsComponent")
        {
            if (params->Count() == 1)
            {
                IPrimitive* primitive = params->Get<IPrimitive*>(0);
                _components.Insert(new PhysicsComponent(parent, primitive));
                delete params;
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type));
        }
    }


    void PhysicsService::Update(float deltaSeconds)
    {
        for (IComponent* component : _components)
        {
            PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(component);
            if (!physicsComponent || physicsComponent->Paused)
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

    void PhysicsService::stepComponent(PhysicsComponent* host, float seconds, int iteration)
    {
        const bool printDebug = false;
        if (printDebug)
        {
            fmt::print("Substep iteration #{}, current velocity: {}\n", iteration, host->Velocity.ToString());
        }
        if (iteration >= MAX_SUBSTEPS)
        {
            fmt::print("Physics component substep overflow\n");
            return;
        }
        if (seconds <= 0.0f || (PhysicsUtilities::NearlyZero(host->Acceleration) && PhysicsUtilities::NearlyZero(host->Velocity)) || host->Paused)
        {
            return;
        }
        float semiMajorAxis = host->GetPrimitive()->SemiMajorAxis();
        float searchDistance = host->Velocity.LengthSquared() * seconds + semiMajorAxis * semiMajorAxis;

        Vector3 v = host->Velocity * seconds;
        Vector3 vN = v.Normalize();
        Vector3 delta = v;
        bool impact = false;

        GJK::CollisionType status = GJK::CollisionType::None;
        VertexList debug = VertexList({host->GetPosition() + host->Velocity * 2, host->GetPosition()});


        std::vector<PhysicsComponent*> targets = getComponentsWithinDistance(host, searchDistance);
        std::vector<SweepResult> collisions = std::vector<SweepResult>();
        for (int i = 0; i < targets.size(); i++)
        {
            if (printDebug)
            {
                fmt::print("Calculating distance between shape #{}\n", i);
            }
            PhysicsComponent* target = targets[i];
            // Make sure we aren't sweeping against ourself
            if (host == target)
            {
                continue;
            }

            SweepResult sweep = PhysicsUtilities::Sweep(*host->GetPrimitive(), *target->GetPrimitive(), v + vN * Vector3::Epsilon(), &debug);
            // Collision found with sweep algorithm
            if (sweep.Hit())
            {
                debug.Append(VertexList{Vector3::Zero(), sweep.GetNormal()});
                impact = true;
                float distance = sweep.GetDistance();
                for (int i = 0; i <= collisions.size(); i++)
                {
                    if (i == collisions.size())
                    {
                        collisions.emplace_back(sweep);
                        break;
                    }
                    if (distance <= collisions[i].GetDistance())
                    {
                        collisions.emplace(collisions.begin() + i, sweep);
                        break;
                    }
                }
            }
        }
        if (impact)
        {
            float vMag = v.Length();
            SweepResult sweep = collisions[0];
            if (sweep.Penetrating())
            {
                // host->Paused = true;
                delta = sweep.GetNormal() * 0.1f;
            }
            else if (sweep.Hit())
            {
                if (printDebug)
                {
                    fmt::print("Attempted move magnitude {}, final magnitude {}\n", vMag, sweep.GetDistance());
                }
                delta -= (vMag - sweep.GetDistance() + Vector3::Epsilon() / vN.Dot(sweep.GetNormal())) * vN;
                host->Velocity -= (host->Velocity.Dot(sweep.GetNormal()) * sweep.GetNormal());

                if (vMag != 0.0f)
                {
                    seconds -= sweep.GetDistance() / host->Velocity.Length();
                }

                // delta -= (sweep.GetNormal() * Vector3::Epsilon());

            }
            /* for (SweepResult sweep : collisions)
            {
                if (sweep.Hit() && !sweep.Penetrating())
                {
                    delta -= (sweep.GetNormal() * Vector3::Epsilon());
                }
            } 
            _debugRenderer->ClearWireframe();
            _debugRenderer->LoadWireframeData(debug); */
        }
        // Don't make veryy small moves. This should prevent sliding
        Vector3 newPosition = host->GetPosition() + delta;
        if (newPosition.Z <= KILL_Z)
        {
            newPosition.Z = KILL_Z;
            host->Velocity.Z = 0.0f;
        }
        if (delta.LengthSquared() > Vector3::Epsilon() * Vector3::Epsilon())
        {
            host->SetPosition(newPosition);
        }
        if (impact && ( seconds >= Vector3::Epsilon() ) && (!PhysicsUtilities::NearlyZero(host->Velocity) ) )
        {
            stepComponent(host, seconds, iteration + 1);
        }
        else if(host->Velocity.LengthSquared() <= Vector3::Epsilon())
        {
            host->Velocity = Vector3::Zero();
        }
    }
    
    void PhysicsService::stepComponent(PhysicsComponent* host, float seconds)
    {
        host->Velocity += host->Acceleration * seconds;
        stepComponent(host, seconds, 0);
    }
}