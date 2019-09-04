#include "stdafx.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Meme
{
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{				
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderAPI::ToggleDepthMask(bool state)
	{
		if (state)
		{
			glDepthFunc(GL_LESS);
		}
		else
		{
			glDepthFunc(GL_LEQUAL);
		}
	}
}
