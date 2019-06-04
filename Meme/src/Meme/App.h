#pragma once

#include "core.h"
#include "Window.h"

#include "Meme/Events/ApplicationEvent.h"

namespace Meme {
	
	class MEME_API App
	{
	public:
		App();
		virtual ~App();
		void OnEvent(Event & e);
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;
	};

	App* CreateApplication();

}