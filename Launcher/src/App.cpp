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
		MEME_INFO("ExampleLayer::Update");
	}

	void OnEvent(Meme::Event& e) override
	{
		MEME_TRACE("{0}", e);
	}
};

class Launcher : public Meme::App
{
public:
	Launcher()
	{
		PushLayer(new ExampleLayer());
	}
	~Launcher()
	{

	}
	
};

Meme::App* Meme::CreateApplication()
{
	return new Launcher();
}
