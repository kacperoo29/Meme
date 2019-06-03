#include "stdafx.h"

#include "app.h"

#include "meme/log.h"
#include "meme/events/ApplicationEvent.h"

namespace Meme {

	App::App()
	{
	}


	App::~App()
	{
	}

	void App::Run()
	{
		WindowResizeEvent e(1280, 720);
		MEME_TRACE(e);

		while (true);
	}

}
