#pragma once

#include "core.h"
#include "Window.h"

#include "Meme/LayerStack.h"
#include "Meme/Events/Event.h"
#include "Meme/Events/ApplicationEvent.h"
#include "Meme/imgui/imguiLayer.h"
#include "Meme/Renderer/Shader.h"
#include "Meme/Renderer/Buffer.h"
#include "Meme/Renderer/VertexArray.h"

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

		inline Window& GetWindow() { return *m_window; }
		inline static App& Get() { return *s_instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		imguiLayer* m_imguiLayer;
		bool m_isRunning = true;
		LayerStack m_layerStack;

		static App* s_instance;

		//TODO: TETING ONLY			
		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_Shader2;
	};

	App* CreateApplication();

}