#pragma once

#include "RenderCommand.h"
#include "Meme/Renderer/Shader.h"
#include "Camera.h"
#include "Texture.h"

namespace Meme {

	class Renderer {
	public:
		static void BeginScene(const Ref<Camera>& camera);
		static void EndScene();

		static void SubmitSkybox(const Ref<VertexArray>& vertexArray,
			const Ref<Shader>& shader,
			const Ref<Cubemap>& cubemap);
		static void Submit(const Ref<VertexArray>& vertexArray,
			const Ref<Shader>& shader,
			const Ref<Texture>& texture,
			const glm::mat4& model = glm::mat4(1.0f));
		

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
			
	private:
		static Ref<Camera> s_Camera;

	};
}