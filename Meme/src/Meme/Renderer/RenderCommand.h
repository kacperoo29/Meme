#pragma once

#include "RenderAPI.h"

namespace Meme {

	class RenderCommand
	{
	public:
		inline static void Clear() { s_RenderAPI->Clear(); }
		inline static void SetClearColor(const glm::vec4& color) { s_RenderAPI->SetClearColor(color); }

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { s_RenderAPI->DrawIndexed(vertexArray); }

	private:
		static RenderAPI* s_RenderAPI;

	};

}
