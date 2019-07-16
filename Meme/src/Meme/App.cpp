#include "stdafx.h"

#include "App.h"
#include "Input.h"
#include "Meme/Renderer/RenderCommand.h"
#include "Meme/Renderer/Renderer.h"


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
