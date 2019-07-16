#include "stdafx.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Meme {

	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::NONE:
			assert(false, "RendererAPI::NONE not supported");
			return nullptr;

		case  RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(verticies, size);
		}

		assert(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::NONE:
			assert(false, "RendererAPI::NONE not supported");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		assert(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
