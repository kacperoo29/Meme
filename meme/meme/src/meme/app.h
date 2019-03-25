#pragma once

#include "core.h"

namespace meme {
	
	class MEME_API App
	{
	public:
		App();
		virtual ~App();
		void run();
	};

	App* CreateApplication();

}