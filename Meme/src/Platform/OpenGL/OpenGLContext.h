#pragma once

#include "Meme/Renderer/Context.h"

struct GLFWwindow;

namespace Meme {

	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_handle;

	};

}