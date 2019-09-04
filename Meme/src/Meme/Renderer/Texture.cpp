#include "stdafx.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Meme {

	Texture* Texture::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::NONE:
			assert(false, "RendererAPI::NONE not supported");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(path);
		}

		assert(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Cubemap* Cubemap::Create(const std::string path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::NONE:
			assert(false, "RendererAPI::NONE not supported");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLCubemap(path);
		}

		assert(false, "Unknown RendererAPI!");
		return nullptr;
	}

}