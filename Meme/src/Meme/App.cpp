#include "stdafx.h"

#include "App.h"
#include "Input.h"

#include <glad/glad.h>

namespace Meme {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	App* App::s_instance = nullptr;

	App::App()
	{
		assert(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(BIND_EVENT_FN(App::OnEvent));

		m_imguiLayer = new imguiLayer();
		PushOverlay(m_imguiLayer);

		m_SquareVA.reset(VertexArray::Create());

		float square[] =
		{
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB; 
		squareVB.reset(VertexBuffer::Create(square, sizeof(square)));
		squareVB->SetLayout({
			{ ShaderDataType::Vec3, "a_Position" }
		});		
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vs2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;		
			
			out vec3 v_Position;		

			void main()
			{
				v_Position = a_Position;				
				gl_Position = vec4(a_Position, 1.0);
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

		m_Shader2.reset(Shader::Create(vs2, fs2));
	}


	App::~App()
	{

	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher disp(e);
		disp.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void App::Run()
	{
		while (m_isRunning)
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader2->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_imguiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImguiRender();
			m_imguiLayer->End();

			m_window->OnUpdate();
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}

}
