#include "stdafx.h"

#include "Win32Window.h"
#include "Meme/Events/ApplicationEvent.h"
#include "Meme/Events/MouseEvent.h"
#include "Meme/Events/KeyEvent.h"

namespace Meme {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		MEME_CORE_ERROR("GLFW error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new Win32Window(props);
	}

	Win32Window::Win32Window(const WindowProps& props)
	{
		Init(props);
	}

	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::Init(const WindowProps& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		MEME_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			assert(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_window,
			[](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowResizeEvent e(width, height);
				data.width = width;
				data.height = height;
				data.EventCallback(e);
			}
		);

		glfwSetWindowCloseCallback(m_window,
			[](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e;
				data.EventCallback(e);
			}
		);

		glfwSetKeyCallback(m_window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			}
		);


		glfwSetMouseButtonCallback(m_window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			}
		);

		glfwSetScrollCallback(m_window,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			}
		);

		glfwSetCursorPosCallback(m_window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			}
		);
	}

	void Win32Window::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void Win32Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void Win32Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enabled;
	}

	bool Win32Window::IsVSync() const
	{
		return m_data.VSync;
	}

}