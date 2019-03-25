#pragma once

#include "core.h"

namespace Meme {
	
	class MEME_API App
	{
	public:
		App();
		virtual ~App();
		void run();
	};

	App* CreateApplication();

}