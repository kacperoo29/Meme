#include <meme.h>

#include "imgui.h"

class ExampleLayer : public Meme::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")
	{	
		m_Camera = std::make_shared<Meme::Camera>(
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

		std::string vs2 = Meme::File("res/basic.vs");
		std::string fs2 = Meme::File("res/basic.fs");
		m_Shader2.reset(Meme::Shader::Create(vs2, fs2));
	}

	virtual void OnUpdate(Meme::Timestep timestep) override
	{
		MEME_TRACE("Delta time: {0}s, ({1}ms)", timestep.GetSeconds(), timestep.GetMilliseconds());
		if (Meme::Input::IsKeyPressed(MEME_KEY_A))
			m_CameraPosition.x -= 0.5f * timestep;
		else if (Meme::Input::IsKeyPressed(MEME_KEY_D))
			m_CameraPosition.x += 0.5f * timestep;

		if (Meme::Input::IsKeyPressed(MEME_KEY_W))
			m_CameraPosition.z += 0.5f * timestep;
		else if (Meme::Input::IsKeyPressed(MEME_KEY_S))
			m_CameraPosition.z -= 0.5f * timestep;

		if (Meme::Input::IsKeyPressed(MEME_KEY_Q))
			m_CameraRotation.y -= 25.0f * timestep;
		else if (Meme::Input::IsKeyPressed(MEME_KEY_E))
			m_CameraRotation.y += 25.0f * timestep;

		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->SetRotation(m_CameraRotation);

		Meme::RenderCommand::SetClearColor({ 0.8f, 0.4f, 0.8f, 1.0f });
		Meme::RenderCommand::Clear();

		Meme::Renderer::BeginScene(*m_Camera);
		Meme::Renderer::Submit(m_SquareVA, m_Shader2);
		Meme::Renderer::EndScene();
	}	

	bool OnKeyPressed(Meme::KeyPressedEvent& e) 
	{
		switch (e.GetKeycode())
		{

		}

		return false;
	}

	virtual void OnEvent(Meme::Event& e) override 
	{
		if (e.GetEventType() == Meme::EventType::WindowResize)
			m_Camera->OnWindowResize();

		Meme::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Meme::KeyPressedEvent>(BIND_EVENT_FUNCTION(ExampleLayer::OnKeyPressed));
	}

	virtual void OnImguiRender() override
	{
		ImGui::Begin("test");		
		ImGui::SliderFloat3("position", &m_CameraPosition.x, -5.f, 5.f);
		ImGui::SliderFloat2("rotation", &m_CameraRotation.x, -180.f, 180.f);
		ImGui::End();	
	}

private:
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, -1.0f };
	glm::vec2 m_CameraRotation = { 0.0f, 0.0f };

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
