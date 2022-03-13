#include "Plane.h"

#include "VertexTypes/VertexPositionTexture.h"

namespace Ceres
{
	using Vertex = VertexPositionTexture;
	Plane::Plane()
		:_vAO(VertexPositionTextureLayout::Get()), _vBO(4, VertexPositionTextureLayout::Get()), _iBO(6)
	{
		const VertexPositionTexture data[] = {
			Vertex(Vector2(-1.0,  1.0f), Vector2(0.0f, 1.0f)),
			Vertex(Vector2( 1.0,  1.0f), Vector2(1.0f, 1.0f)),
			Vertex(Vector2(-1.0, -1.0f), Vector2(0.0f, 0.0f)),
			Vertex(Vector2( 1.0, -1.0f), Vector2(1.0f, 0.0f))
		};
		const unsigned int indices[] = {2, 1, 0, 1, 2, 3};
		_vBO.SetData(data, 4);
		_vAO.SetAttributes();
		_iBO.SetData(indices, 6);
	}

	Plane::~Plane()
	{}

	const VertexArrayObject& Plane::GetVertexArray() const
	{
		return _vAO;
	}

	const IndexBuffer& Plane::GetIndexBuffer() const
	{
		return _iBO;
	}
}