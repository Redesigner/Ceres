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
        Vector3 vN = v.Normalize();
        Vector3 vResult = v;

        Vector3 d = Vector3::Zero();
        Vector3 dN = Vector3::Zero();

        Vector3 delta = v;

        bool impact = false;

        PhysicsComponent* firstImpact = host;
        GJK::CollisionType status = GJK::CollisionType::None;

        std::vector<PhysicsComponent*> targets = _getComponentsWithinDistance(host, searchDistance);
        for (PhysicsComponent* target : targets)
        {
            if (host == target) { continue; }

            VertexList debug = VertexList();
            SweepResult sweep = PhysicsUtilities::Sweep(*host->GetPrimitive(), *target->GetPrimitive(), v + vN * Vector3::Epsilon(), &debug);
            // Collision found with sweep algorithm
            if (sweep.Hit())
            {
                Vector3 shortest;
                // GJK shortestMove = GJK(host, target);
                // status = shortestMove.Solve(&shortest, &dN);

                _debugRenderer->ClearWireframe();
                debug.Append(VertexList{host->GetPosition(), host->GetPosition() + sweep.GetNormal()});
                _debugRenderer->LoadWireframeData(debug);

                delta = sweep.GetDelta();
            }
        }
        if (delta.LengthSquared() < Vector3::Epsilon() * Vector3::Epsilon()) { return; }
        host->SetPosition(host->GetPosition() + delta);
    }
}