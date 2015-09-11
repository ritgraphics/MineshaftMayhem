
#include <vix_game.h>

using namespace Vixen;

class EndlessRunner : public IGame
{
public:
	EndlessRunner();

	void VOnStartup();
	void VOnShutdown();
	void VOnUpdate(float dt);
	void VOnRender(float dt);

private:
	
};

EndlessRunner::EndlessRunner()
	: IGame()
{

}

void EndlessRunner::VOnStartup()
{
	m_renderer->VSetClearColor(Vixen::Colors::CornflowerBlue);
}

void EndlessRunner::VOnUpdate(float dt)
{
	
}

void EndlessRunner::VOnRender(float dt)
{
	
}

void EndlessRunner::VOnShutdown()
{
	
}



int main(int argc, char* argv[])
{
	EndlessRunner _game;

	return _game.Run();
}