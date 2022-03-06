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


    ComponentRef PhysicsService::GenerateComponent(Type type, ComponentPR& params)
    {
        if (type == Type(typeid(PhysicsComponent)))
        {
            if (params->Count() == 1)
            {
                std::shared_ptr<IPrimitive> primitive = params->Get<std::shared_ptr<IPrimitive>>(0);
                _components.Insert(new PhysicsComponent(primitive));
                return ComponentRef(&_components, _components.Size() - 1);
            }
            else
            {
                throw std::invalid_argument(fmt::format("Invalid argument count: {}.", type.name()));
            }
        }
        else
        {
            throw std::invalid_argument(fmt::format("Unable to generate component of type {}.", type.name()));
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

                const float frictionCo = host->Friction;
                const float normalCo = -Vector3::Up().Dot(sweep.GetNormal());
                float friction = frictionCo * std::pow(normalCo, 16); // not realistic to have normal coefficient squared
                Vector3 frictionLoss = friction * seconds * Vector3(vN.X, vN.Y, 0.0f);

                const bool xComparison = std::abs(frictionLoss.X) >= std::abs(host->Velocity.X);
                const bool yComparison = std::abs(frictionLoss.Y) >= std::abs(host->Velocity.Y);
                if (vMag != 0.0f)
                {
                    seconds -= sweep.GetDistance() / host->Velocity.Length();
                }

                if (xComparison)
                {
                    host->Velocity.X = 0.0f;
                    frictionLoss.X = 0.0f;
                }
                if (yComparison)
                {
                    host->Velocity.Y = 0.0f;
                    frictionLoss.Y = 0.0f;
                }
                host->Velocity -= frictionLoss;

                host->OnHit(sweep);
                if (sweep.GetNormal().Z <= - 0.7f)
                {
                    host->SetGrounded(true);
                }
            }
        }
        else if (iteration == 0)
        {
            host->SetGrounded(false);
        }
        Vector3 newPosition = host->GetPosition() + delta;
        if (newPosition.Z <= KILL_Z)
        {
            newPosition = Vector3::Zero();
            host->Velocity = Vector3::Zero();
        }
        host->SetPosition(newPosition);
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
        host->Acceleration = Vector3::Zero();
        host->Velocity += Vector3::Up() * -9.8f * seconds;
        stepComponent(host, seconds, 0);
        const float planarSpeed2 = (host->Velocity.X) * (host->Velocity.X) + (host->Velocity.Y) * (host->Velocity.Y);
        if (planarSpeed2 >= host->MaxSpeed * host->MaxSpeed)
        {
            const float planarSpeed = std::sqrt(planarSpeed2);
            host->Velocity.X = host->Velocity.X / planarSpeed * host->MaxSpeed;
            host->Velocity.Y = host->Velocity.Y / planarSpeed * host->MaxSpeed;
        }
        host->FinalizeVelocity();
    }
}