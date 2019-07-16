#pragma once

#include "RenderCommand.h"
#include "Meme/Renderer/Shader.h"
#include "Camera.h"

namespace Meme {

	class Renderer {
	public:
		static void BeginScene(Camera& camera);		
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, 
			const std::shared_ptr<Shader>& shader);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
			
	private:
		static Camera* s_Camera;

	};
}