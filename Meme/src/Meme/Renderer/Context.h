#pragma once

namespace Meme {

	class Context
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	private:

	};

}