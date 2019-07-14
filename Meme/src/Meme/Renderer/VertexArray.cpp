#include "stdafx.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Meme {

	VertexArray* Meme::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			assert(false, "RendererAPI::NONE not supported");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		assert(false, "Unknown RendererAPI!");
		return nullptr;
	}

}