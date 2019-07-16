#pragma once

#include "Meme/Renderer/Shader.h"

namespace Meme {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

	};

}
