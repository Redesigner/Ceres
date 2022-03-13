#pragma once

#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include "VertexTypes/VertexPositionTextureLayout.h"

namespace Ceres
{
	class Plane
	{
		public:
			/// Container of OpenGL objects for rendering an image directly to the screen.
			/// Each OpenGL instance really only needs one of these.
			/// Setting the bounds and size of the sprite should be done with a
			/// transformation Matrix.
			Plane();
			~Plane();

            const VertexArrayObject& GetVertexArray() const;
            const IndexBuffer& GetIndexBuffer() const;
			
		private:
            IndexBuffer _iBO;
            VertexArrayObject _vAO;
            VertexBufferObject _vBO;
	};
}