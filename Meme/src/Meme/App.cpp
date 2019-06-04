#include "stdafx.h"

#include "app.h"

#include "meme/log.h"
#include "meme/events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Meme {

	App::App()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
	}


	App::~App()
	{
	}

	void App::Run()
	{
		WindowResizeEvent e(1280, 720);
		MEME_TRACE(e);

		while (m_isRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}

}
