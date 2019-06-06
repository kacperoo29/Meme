#pragma once

#include "core.h"
#include "Window.h"

#include "Meme/LayerStack.h"
#include "Meme/Events/Event.h"
#include "Meme/Events/ApplicationEvent.h"

namespace Meme {
	
	class MEME_API App
	{
	public:
		App();
		virtual ~App();


		void OnEvent(Event & e);
		void Run();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
			

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;
		LayerStack m_layerStack;
	};

	App* CreateApplication();

}