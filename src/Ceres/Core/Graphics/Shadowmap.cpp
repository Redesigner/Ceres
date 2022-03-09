#include "Shadowmap.h"

namespace Ceres
{
	Shadowmap::Shadowmap(unsigned int resolution, AssetPtr<Effect> effect)
		: _resolution(resolution), _effect(effect)
	{
		glGenFramebuffers(1, &_fBO);
		
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _resolution, _resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindFramebuffer(GL_FRAMEBUFFER, _fBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _id, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		// Unbind the framebuffer we created for the shadow map
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		_lightPosition = Vector3(0, -20.0f, 10.0f);
		_projection = Matrix::LookAt(_lightPosition, Vector3::Zero(), Vector3::Up()) * Matrix::Orthographic(20.0f, 20.0f, 5.0f, 35.0f);

		// _projection = Matrix::Scale(0.1f, 0.1f, 0.1f) * Matrix::LookAt(Vector3::Zero(), _lightPosition, Vector3::Up());
	}
	
	Shadowmap::~Shadowmap()
	{
		glDeleteTextures(1, &_id);
		glDeleteFramebuffers(1, &_fBO);
	}

	void Shadowmap::Bind()
	{
		glViewport(0, 0, _resolution, _resolution);
		glBindFramebuffer(GL_FRAMEBUFFER, _fBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		_effect->Begin();
		_effect->SetMatrix("lightspace", _projection);
	}

	void Shadowmap::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint Shadowmap::GetID() const
	{
		return _id;
	}

	void Shadowmap::SetModelMatrix(Matrix& matrix)
	{
		_effect->SetMatrix("model", matrix);
	}

	void Shadowmap::SetPosition(Vector3 position)
	{
		_projection = Matrix::LookAt(
			_lightPosition + position,
			position,
			Vector3::Up()
		) * Matrix::Orthographic(20.0f, 20.0f, 0.1f, 100.0f);
	}

	const Matrix& Shadowmap::GetMatrix() const
	{
		return _projection;
	}
}