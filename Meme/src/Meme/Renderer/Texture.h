#pragma once

namespace Meme {

	class Texture
	{
	public:
		virtual void Bind(uint32_t slot = 0) = 0;
		virtual void Unbind() = 0;

		static Texture* Create(const std::string& path);
	};

	class Cubemap
	{
	public:

		virtual void Bind(uint32_t slot = 0) = 0;
		virtual void Unbind() = 0;

		static Cubemap* Create(const std::string path);
	};


}