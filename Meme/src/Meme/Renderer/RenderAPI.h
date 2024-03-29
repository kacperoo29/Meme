#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Meme {

	class RenderAPI
	{
	public:
		enum class API
		{
			NONE = 0, OpenGL = 1
		};

		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void ToggleDepthMask(bool state) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};

}

