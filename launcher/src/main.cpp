#include <meme.h>

class Launcher : public Meme::App
{
public:
	Launcher()
	{

	}
	~Launcher()
	{

	}
	
};

Meme::App* Meme::CreateApplication()
{
	return new Launcher();
}
