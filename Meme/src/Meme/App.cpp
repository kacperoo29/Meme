#include "stdafx.h"

#include "App.h"
#include "Input.h"
#include <chrono>

namespace Meme {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	App* App::s_instance = nullptr;

	App::App()
	{
		assert(!s_instance, "Application already exists!");
		s_instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(App::OnEvent));	
		m_Window->SetVSync(true);

		m_imguiLayer = new ImGuiLayer();
		PushOverlay(m_imguiLayer);		
			   		 		
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
			auto start = std::chrono::high_resolution_clock::now();
			Timestep timestep = m_LastFrameTime;			

			for (Layer* layer : m_layerStack)
				layer->OnUpdate(timestep);

			m_imguiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImguiRender();
			m_imguiLayer->End();

			m_Window->OnUpdate();

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> diff = end - start;
			m_LastFrameTime = diff.count();

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
