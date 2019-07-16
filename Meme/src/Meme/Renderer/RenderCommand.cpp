#include "stdafx.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Meme {

	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI;

}