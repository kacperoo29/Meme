#pragma once

#include "stdafx.h"

#include "Meme/Core.h"
#include "Meme/Events/Event.h"

namespace Meme {

	struct WindowProps
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProps(const std::string& title = "Meme Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: title(title), width(width), height(height)
		{
		}
	};
	
	class MEME_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
		
	};

}