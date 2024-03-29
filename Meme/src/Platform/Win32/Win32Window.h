#pragma once

#include "Meme/Window.h"
#include "Platform/OpenGL/OpenGLContext.h"

struct GLFWwindow;

namespace Meme {

	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProps& props);
		virtual ~Win32Window();

		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return m_data.width; }
		inline uint32_t GetHeight() const override { return m_data.height; }
		
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Context* m_context;

		struct WindowData
		{
			std::string title;
			uint32_t width, height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_data;
	};

}