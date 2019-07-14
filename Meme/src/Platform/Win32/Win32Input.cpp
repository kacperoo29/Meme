#include "stdafx.h"
#include "Win32Input.h"

#include "Meme/App.h"
#include <GLFW/glfw3.h>


namespace Meme {

	Input* Input::s_Instance = new Win32Input();

	bool Win32Input::IsKeyPressedImpl(int32_t keycode)
	{
		auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Win32Input::IsMouseButtonPressedImpl(int32_t button)
	{
		auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> Win32Input::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}


	float Win32Input::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float Win32Input::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}