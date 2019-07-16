#include <meme.h>

#include "imgui.h"

class ExampleLayer : public Meme::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")
	{	
		m_Camera = m_Camera = std::make_shared<Meme::Camera>(
			Meme::App::Get().GetWindow().GetWidth(),
			Meme::App::Get().GetWindow().GetHeight(),
			65.f);

		m_SquareVA.reset(Meme::VertexArray::Create());

		float square[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Meme::VertexBuffer> squareVB;
		squareVB.reset(Meme::VertexBuffer::Create(square, sizeof(square)));
		squareVB->SetLayout({
			{ Meme::ShaderDataType::Vec3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Meme::IndexBuffer> squareIB;
		squareIB.reset(Meme::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vs2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;		
			
			out vec3 v_Position;

			uniform mat4 u_VP;		

			void main()
			{
				v_Position = a_Position;				
				gl_Position = u_VP * vec4(a_Position, 1.0);
			}
		)";

		std::string fs2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{				
				color = vec4((v_Position + 0.3) * 0.5 , 1.0);
			}
		)";

		m_Shader2.reset(Meme::Shader::Create(vs2, fs2));
	}

	virtual void OnUpdate() override
	{
		m_Camera->SetPosition(m_position);
		m_Camera->SetRotation(m_rotation);

		Meme::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Meme::RenderCommand::Clear();

		Meme::Renderer::BeginScene(*m_Camera);
		Meme::Renderer::Submit(m_SquareVA, m_Shader2);
		Meme::Renderer::EndScene();
	}

	virtual void OnImguiRender() override
	{
		ImGui::Begin("test");		
		ImGui::SliderFloat3("position", &m_position.x, -5.f, 5.f);
		ImGui::SliderFloat2("rotation", &m_rotation.x, -180.f, 180.f);
		ImGui::End();	
	}

private:
	glm::vec3 m_position = { 0.0f, 0.0f, -1.0f };
	glm::vec2 m_rotation = { 0.0f, 0.0f };

	std::shared_ptr<Meme::VertexArray> m_SquareVA;
	std::shared_ptr<Meme::Shader> m_Shader2;
	std::shared_ptr<Meme::Camera> m_Camera;

};

class Launcher : public Meme::App
{
public:
	Launcher()
	{
		PushLayer(new ExampleLayer());		
	}
	~Launcher()
	{

	}
	
};

Meme::App* Meme::CreateApplication()
{
	return new Launcher();
}
