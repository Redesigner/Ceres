#include "PhysicsService.h"

#include "../Components/PhysicsComponent.h"
#include "../Physics/Primitives/CubePrimitive.h"
#include "../Physics/GJK/GJK.h"
#include "../Physics/GJK/Simplex.h"

#include "RenderService.h"
#include "../Graphics/VertexTypes/VertexPosition.h"

#include <stdexcept>
#include <fmt/core.h>

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
            if (argCount == 0)
            {
                _components.Insert(new PhysicsComponent(parent, new CubePrimitive(1)));
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
            if (!physicsComponent) { continue; }
            stepComponent(physicsComponent, deltaSeconds);
        }
    }


    std::vector<PhysicsComponent*> PhysicsService::_getComponentsWithinDistance(PhysicsComponent* sourceComponent, const float distance)
    {
        std::vector<PhysicsComponent*> result = std::vector<PhysicsComponent*>();
        for (IComponent* target : _components)
        {
            PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(target);
            if (!physicsComponent) { continue; }
            if (physicsComponent == sourceComponent) { continue; }

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
        if (seconds <= 0 || host->Velocity == Vector3::Zero()) { return; }
        float semiMajorAxis = host->GetPrimitive()->SemiMajorAxis();
        float searchDistance = host->Velocity.LengthSquared() * seconds + semiMajorAxis * semiMajorAxis;

        Vector3 v = host->Velocity * seconds;
        Vector3 vResult = v;

        Vector3 d = Vector3::Zero();
        Vector3 dN = Vector3::Zero();

        Vector3 delta = v;
        Vector3 maxDelta = v;

        bool impact = false;

        PhysicsComponent* firstImpact = host;
        GJK::CollisionType status = GJK::CollisionType::None;

        std::vector<PhysicsComponent*> targets = _getComponentsWithinDistance(host, searchDistance * 10000.0f);
        for (PhysicsComponent* target : targets)
        {
            if (host == target) { continue; }

            GJK collision = GJK(host, target);
            status = collision.Solve(&d, &dN);


            // fmt::print("\nObjects at {} and {}\n", host->GetPosition().ToString(), target->GetPosition().ToString());
            fmt::print("Distance from target calculated as {}\n\n\n", d.ToString());
            VertexPosition data[] = {VertexPosition(d + host->GetPosition()), VertexPosition(host->GetPosition())};
            int inds[] = {0, 1};
            _debugRenderer->ClearWireframe();
            _debugRenderer->LoadWireframeData(data, inds, 2);


            double dMag = d.Length();

            Vector3 vN = v.Normalize();
            Vector3 vGuess = v;
            bool direct = ( v.Dot(dN) > Vector3::Epsilon());
            if (!direct) { continue; }

            switch (status)
            {
                case GJK::CollisionType::Point:
                    {
                        delta = d.Dot(vN) * vN - (vN * Vector3::Epsilon());
                        break;
                    }
                case GJK::CollisionType::Line:
                    {
                        delta = d.Dot(vN) * vN - (vN * Vector3::Epsilon());
                        break;
                    }
                case GJK::CollisionType::Face:
                    {
                        delta = d.Dot(vN) * vN - (vN * Vector3::Epsilon());
                        vGuess = v - ((v - (d.Dot(vN) * vN)).Dot(dN) * dN) - (dN * Vector3::Epsilon());
                        break;
                    }
            }
            bool near = delta.LengthSquared() < dMag * dMag;
            if (near && delta.LengthSquared() < maxDelta.LengthSquared())
            {
                maxDelta = delta;
                vResult = vGuess;
                firstImpact = target;
                impact = true;
            }
            fmt::print("Objects can travel {} until colliding with at {} along normal {}.\n", delta.ToString(), d.ToString(), dN.ToString());
        }
        if (impact)
        {
            host->SetPosition(host->GetPosition() + (Vector3)maxDelta);
        }
        else
        {
            host->SetPosition(host->GetPosition() + (Vector3)v);
        }
    }
}