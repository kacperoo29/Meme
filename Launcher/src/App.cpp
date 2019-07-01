#include <meme.h>

class ExampleLayer : public Meme::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Meme::Input::IsKeyPressed(MEME_KEY_TAB))
			MEME_TRACE("Tab is pressed!");
	}

	void OnEvent(Meme::Event& e) override
	{
		
	}
};

class Launcher : public Meme::App
{
public:
	Launcher()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Meme::imguiLayer());
	}
	~Launcher()
	{

	}
	
};

Meme::App* Meme::CreateApplication()
{
	return new Launcher();
}
