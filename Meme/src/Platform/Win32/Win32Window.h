#pragma once

#include "Meme/Window.h"

#include <GLFW/glfw3.h>

namespace Meme {

	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProps& props);
		virtual ~Win32Window();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_data.width; }
		inline unsigned int GetHeight() const override { return m_data.height; }
		
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_data;
	};

}