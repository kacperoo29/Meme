#pragma once

#include "Meme/Renderer/RenderAPI.h"

namespace Meme {

	class OpenGLRenderAPI : public RenderAPI
	{
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};

}