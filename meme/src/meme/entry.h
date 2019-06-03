#pragma once

#ifdef _WIN32

extern Meme::App* Meme::CreateApplication();

int main(int argc, char** argv)
{
	Meme::Log::init();
	MEME_CORE_INFO("Log initialized");

	auto app = Meme::CreateApplication();
	app->Run();
	delete app;
}

#endif