#pragma once

#ifdef _WIN32

extern meme::App* meme::CreateApplication();

int main(int argc, char** argv)
{
	auto app = meme::CreateApplication();
	app->run();
	delete app;
}

#endif