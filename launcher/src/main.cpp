#include <meme.h>

class Launcher : public meme::App
{
public:
	Launcher()
	{

	}
	~Launcher()
	{

	}
	
};

meme::App* meme::CreateApplication()
{
	return new Launcher();
}
