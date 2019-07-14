#include "stdafx.h"

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Meme {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_handle(window)
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_handle);
		int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		assert(status, "Failed to initalize glad!");

		MEME_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		MEME_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_handle);
	}
}
