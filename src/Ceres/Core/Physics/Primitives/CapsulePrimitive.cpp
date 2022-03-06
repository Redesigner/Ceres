#include "CapsulePrimitive.h"

namespace Ceres
{
	CapsulePrimitive::CapsulePrimitive(float radius, float halfHeight)
		:ConvexHull(VertexList(2)),
		_radius(radius), _halfHeight(halfHeight)
	{
		_vertices[0] = Vector3(0.0f, 0.0f, _halfHeight);
		_vertices[1] = Vector3(0.0f, 0.0f, -_halfHeight);
	}

	CapsulePrimitive::~CapsulePrimitive()
	{}

	float CapsulePrimitive::SemiMajorAxis()
	{
		return _radius + _halfHeight;
	}

	float CapsulePrimitive::GetSphereRadius() const
	{
		return _radius;
	}
}