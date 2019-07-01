#pragma once

#include "Meme/Layer.h"

#include "Meme/Events/MouseEvent.h"
#include "Meme/Events/KeyEvent.h"
#include "Meme/Events/ApplicationEvent.h"

namespace Meme {

	class MEME_API imguiLayer : public Layer
	{
	public:
		imguiLayer();
		~imguiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& e);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		float m_time = 0.0f;
	};

}

