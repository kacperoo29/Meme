#pragma once

#include "core.h"

namespace Meme {
	
	class MEME_API App
	{
	public:
		App();
		virtual ~App();
		void Run();
	};

	App* CreateApplication();

}