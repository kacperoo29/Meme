#include <meme.h>

#include "imgui.h"

class ExampleLayer : public Meme::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		

	}

	virtual void OnUpdate() override
	{
		if (Meme::Input::IsKeyPressed(MEME_KEY_TAB))
			MEME_TRACE("Tab is pressed!");
	}

	virtual void OnEvent(Meme::Event& e) override
	{
		
	}

	virtual void OnImguiRender() override
	{
		ImGui::Begin("test");
		ImGui::Text("SUKKKKKKK MAH KOK");
		ImGui::End();
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
