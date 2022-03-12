#pragma once

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include "VertexTypes/VertexPositionTextureLayout.h"

namespace Ceres
{
	class Sprite
	{
		public:
			Sprite();
			~Sprite();

            const VertexArrayObject& GetVertexArray() const;
            const IndexBuffer& GetIndexBuffer() const;
			
		private:
            IndexBuffer _iBO;
            VertexArrayObject _vAO;
            VertexBufferObject _vBO;
	};
}