#include "stdafx.h"

#include "app.h"

#include <GLFW/glfw3.h>

namespace Meme {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	App::App()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(BIND_EVENT_FN(App::OnEvent));
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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}

	void App::PushLayer(Layer * layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer * overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	bool App::OnWindowClose(WindowCloseEvent & e)
	{
		m_isRunning = false;
		return true;
	}

}