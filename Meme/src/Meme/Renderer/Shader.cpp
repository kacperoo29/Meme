#include "stdafx.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Meme {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::NONE:
			assert(false, "RendererAPI::NONE not supported");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		assert(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
