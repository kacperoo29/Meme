#pragma once

#include "Event.h"


namespace Meme
{
	class MEME_API KeyEvent : public Event
	{
	public:
		inline int32_t GetKeycode() const { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		KeyEvent(int32_t keycode)
			: m_keycode(keycode) 
		{
		}
		int32_t m_keycode;
	};

	class MEME_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int32_t keycode, int32_t repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount) {}

		inline int32_t GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int32_t m_repeatCount;
	};

	class MEME_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int32_t keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class MEME_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int32_t keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}