#pragma once

#include "RenderAPI.h"

namespace Meme {

	class RenderCommand
	{
	public:
		inline static void Clear() { s_RenderAPI->Clear(); }
		inline static void SetClearColor(const glm::vec4& color) { s_RenderAPI->SetClearColor(color); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RenderAPI->DrawIndexed(vertexArray); }
		inline static void ToggleDepthMask(bool state) { s_RenderAPI->ToggleDepthMask(state); }

	private:
		static RenderAPI* s_RenderAPI;

	};

}
