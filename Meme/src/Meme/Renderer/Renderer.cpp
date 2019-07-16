#include "stdafx.h"
#include "Renderer.h"

namespace Meme {

	Camera* Renderer::s_Camera = new Camera;

	void Renderer::BeginScene(Camera& camera)
	{
		Renderer::s_Camera = &camera;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray,
		const std::shared_ptr<Shader>& shader)
	{		
		shader->Bind();
		shader->UploadUniformMat4f("u_VP", s_Camera->GetVP());

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}