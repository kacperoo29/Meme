#pragma once

#include "Meme/Renderer/Texture.h"

namespace Meme {

	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& path);

		virtual void Bind(uint32_t slot = 0) override;
		virtual void Unbind() override;

	private:
		uint32_t m_ID;

	};

	class OpenGLCubemap : public Cubemap
	{
	public:
		OpenGLCubemap(const std::string& path);

		virtual void Bind(uint32_t slot = 0) override;
		virtual void Unbind() override;

	private:
		uint32_t m_ID;

	};

}