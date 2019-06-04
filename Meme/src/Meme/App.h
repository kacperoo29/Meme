#pragma once

#include "core.h"
#include "Window.h"

namespace Meme {
	
	class MEME_API App
	{
	public:
		App();
		virtual ~App();
		void Run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;
	};

	App* CreateApplication();

}