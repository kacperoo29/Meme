#include "stdafx.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Meme {

	VertexArray* Meme::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::NONE:
			assert(false, "RendererAPI::NONE not supported");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		assert(false, "Unknown RendererAPI!");
		return nullptr;
	}

}