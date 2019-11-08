#include "stdafx.h"
#include "Renderer.h"

#include <glm/ext/matrix_transform.hpp>

namespace Meme {

	Ref<Camera> Renderer::s_Camera = std::make_shared<Camera>();

	void Renderer::BeginScene(const Ref<Camera>& camera)
	{
		Renderer::s_Camera = camera;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::SubmitSkybox(const Ref<VertexArray>& vertexArray,
		const Ref<Shader>& shader,
		const Ref<Cubemap>& cubemap)
	{
		RenderCommand::ToggleDepthMask(false);
	
		shader->Bind();
		glm::mat4 view = glm::mat4(glm::mat3(s_Camera->GetViewMatrix()));	
		shader->UploadUniformMat4f("uView", view);
		shader->UploadUniformMat4f("uProjection", s_Camera->GetProjectionMatrix());
		cubemap->Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		RenderCommand::ToggleDepthMask(true);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray,
		const Ref<Shader>& shader,
		const Ref<Texture>& texture,
		const glm::mat4& model)
	{		
		shader->Bind();
		shader->UploadUniformMat4f("uVP", s_Camera->GetVP());
		shader->UploadUniformMat4f("uModel", model);
		shader->UploadUniform3f("uCameraPos", s_Camera->GetPosition());
		
		texture->Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}