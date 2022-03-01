#pragma once

extern "C"
{
	#include <SDL2/SDL.h>
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
}

#include "../Common/AssetPointer.h"
#include "../Common/Matrix.h"
#include "../Common/Vector3.h"

#include "Effect.h"

namespace Ceres
{
	class Shadowmap
	{
		public:
			Shadowmap(unsigned int resolution, AssetPtr<Effect> effect);
			~Shadowmap();

			void Bind();
			void Unbind();
			GLuint GetID() const;
			void SetModelMatrix(Matrix& model);
			const Matrix& GetMatrix() const;

		private:
			AssetPtr<Effect> _effect;
			GLuint _fBO;
			GLuint _id;
			Vector3 _lightPosition;
			Matrix _projection;
			const unsigned int _resolution;
	};
}