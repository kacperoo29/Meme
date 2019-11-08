#include <meme.h>

#include <glm/ext/matrix_transform.hpp>

#include "imgui.h"

class ExampleLayer : public Meme::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CubePosition(0.0f)
	{
		m_Camera = std::make_shared<Meme::Camera>(
			Meme::App::Get().GetWindow().GetWidth(),
			Meme::App::Get().GetWindow().GetHeight(),
			65.f);



		m_SkyboxVA.reset(Meme::VertexArray::Create());
		Meme::Mesh skybox;
		skybox.LoadOBJ("res/model/untitled.obj");

		Meme::Ref<Meme::VertexBuffer> skyboxVB;
		skyboxVB.reset(Meme::VertexBuffer::Create(skybox.GetVerticesPointer(), skybox.GetVerticesSize()));
		skyboxVB->SetLayout({
			{ Meme::ShaderDataType::Vec3, "a_Position" },
			{ Meme::ShaderDataType::Vec2, "a_TexCoord" },
			{ Meme::ShaderDataType::Vec3, "a_Normal" }
			});
		m_SkyboxVA->AddVertexBuffer(skyboxVB);

		Meme::Ref<Meme::IndexBuffer> skyboxIB;
		skyboxIB.reset(Meme::IndexBuffer::Create(skybox.GetIndicesPointer(), skybox.GetIndicesSize()));
		m_SkyboxVA->SetIndexBuffer(skyboxIB);

		m_SquareVA.reset(Meme::VertexArray::Create());
		Meme::Mesh model;
		model.LoadOBJ("res/model/untitled.obj");

		Meme::Ref<Meme::VertexBuffer> squareVB;
		squareVB.reset(Meme::VertexBuffer::Create(model.GetVerticesPointer(), model.GetVerticesSize()));
		squareVB->SetLayout({
			{ Meme::ShaderDataType::Vec3, "a_Position" },
			{ Meme::ShaderDataType::Vec2, "a_TexCoord" },
			{ Meme::ShaderDataType::Vec3, "a_Normal" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		Meme::Ref<Meme::IndexBuffer> squareIB;
		squareIB.reset(Meme::IndexBuffer::Create(model.GetIndicesPointer(), model.GetIndicesSize()));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_SkyboxShader.reset(Meme::Shader::Create("res/shader/skybox.vs", "res/shader/skybox.fs"));
		m_Shader.reset(Meme::Shader::Create("res/shader/basic.vs", "res/shader/basic.fs"));

		m_SkyboxCubemap.reset(Meme::Cubemap::Create("res/texture/skybox"));
		m_Texture.reset(Meme::Texture::Create("res/texture/cube.jpg"));

		Meme::RenderCommand::SetClearColor({ 0.8f, 0.4f, 0.8f, 1.0f });
	}

	virtual void OnUpdate(Meme::Timestep timestep) override
	{
		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->SetRotation(m_CameraRotation);

		Meme::RenderCommand::Clear();
		Meme::Renderer::BeginScene(m_Camera);

		std::vector<std::future<glm::mat4>> futures;

		for (int z = 0; z < 25; ++z)
		{
			for (int y = 0; y < 25; ++y)
			{
				for (int x = 0; x < 25; ++x)
				{
					futures.push_back(std::async(std::launch::async, &ExampleLayer::transform, this, x, y, z));

					//glm::vec3 pos(x * .5f, y * .5f, z * .5f);
					//pos += m_CubePosition;
					//glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					//Meme::Renderer::Submit(m_SquareVA, m_Shader, m_Texture, transform);
				}
			}
		}

		for (auto& future : futures)
		{
			Meme::Renderer::Submit(m_SquareVA, m_Shader, m_Texture, future.get());
		}

		Meme::Renderer::SubmitSkybox(m_SkyboxVA, m_SkyboxShader, m_SkyboxCubemap);
		Meme::Renderer::EndScene();
		MEME_INFO("Frame took {0} ms", timestep.GetMilliseconds());
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
		ImGui::SliderFloat3("Camera Position", &m_CameraPosition.x, -50.f, 50.f);
		ImGui::SliderFloat2("Camera Rotation", &m_CameraRotation.x, -180.f, 180.f);
		ImGui::SliderFloat3("Cube Position", &m_CubePosition.x, -50.f, 50.f);

		ImGui::End();
	}

	glm::mat4 transform(int x, int y, int z)
	{
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
		std::lock_guard<std::mutex> lk(m_Mutex);
		glm::vec3 pos(x * .5f, y * .5f, z * .5f);
		pos += m_CubePosition;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		return transform;
	}

private:
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	glm::vec2 m_CameraRotation = { 0.0f, 0.0f };

	Meme::Ref<Meme::VertexArray> m_SquareVA;
	Meme::Ref<Meme::Shader> m_Shader;
	Meme::Ref<Meme::Texture> m_Texture;
	Meme::Ref<Meme::VertexArray> m_SkyboxVA;
	Meme::Ref<Meme::Shader> m_SkyboxShader;
	Meme::Ref<Meme::Cubemap> m_SkyboxCubemap;
	Meme::Ref<Meme::Camera> m_Camera;

	glm::vec3 m_CubePosition;

	std::mutex m_Mutex;


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
