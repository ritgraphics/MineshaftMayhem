
#include <vix_game.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <vix_font.h>
#include <vix_gameobject.h>

using namespace Vixen;

class EndlessRunner : public Game
{
public:
	EndlessRunner();

	void VOnStartup();
	void VOnShutdown();
	void VOnUpdate(float dt);
	void VOnRender(float dt);

private:
	ICamera3D*  m_camera3D;
	IModel*     m_floor;
	IModel*     m_player;
	IFont*      m_font;
	GameObject* m_go;
	GameObject* m_po;
	Transform   fontTransform;
};

EndlessRunner::EndlessRunner()
	: Game()
{

}

void EndlessRunner::VOnStartup()
{
	m_renderer->VSetClearColor(Vixen::Colors::Black);

	m_camera3D = m_renderer->Camera3D();
	m_camera3D->VSetView(Vector3(0.0f, 5.0f,  -5.0f), Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	m_camera3D->VSetSpeed(50.0f);

	m_floor = ResourceManager::OpenModel(VTEXT("floor.mdl"));
	m_player = ResourceManager::OpenModel(VTEXT("cube.mdl"));
	m_font = ResourceManager::OpenFont(VTEXT("Consolas_24.fnt"));



	m_go = new GameObject(Transform(0.0f, -5.0f, 5.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f));
	m_go->SetModel(m_floor);

	m_po = new GameObject(Transform(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
	m_po->SetModel(m_player);

	fontTransform = Transform(20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	

	m_window->VToggleCursor();
}

void EndlessRunner::VOnUpdate(float dt)
{
	if (Input::SingleKeyPress(IKEY::F2))
		m_window->VClose();

	if (Input::KeyPress(IKEY::S))
		m_camera3D->VWalk(-dt);

	if (Input::KeyPress(IKEY::W))
		m_camera3D->VWalk(dt);

	if (Input::KeyPress(IKEY::A))
		m_camera3D->VStrafe(-dt);

	if (Input::KeyPress(IKEY::D))
		m_camera3D->VStrafe(dt);

	if (Input::KeyPress(IKEY::UP))
	{
		m_go->GetTransform()->TranslateY(dt);
	}


	int deltaX = Input::DeltaX(m_window->VGetClientBounds().w / 2);
	int deltaY = Input::DeltaY(m_window->VGetClientBounds().h / 2);
	m_camera3D->VRotateX(deltaY * 0.25f);
	m_camera3D->VRotateY(deltaX * 0.25f);


	m_camera3D->VUpdate(dt);

	m_window->VTrapCursorCenter();
}

void EndlessRunner::VOnRender(float dt)
{
	
	m_go->Render(m_camera3D);
	m_po->Render(m_camera3D);

	//ALL 2D UI IS DRAW AFTER SCENE IS DRAWN
	USStream ss;
	ss << "FPS: " << m_window->VFPS();
	m_renderer->VRenderText2D(m_font, ss.str(), fontTransform);
}

void EndlessRunner::VOnShutdown()
{
    delete m_player;
	delete m_floor;
	delete m_font;
}



int main(int argc, char* argv[])
{
	EndlessRunner _game;

	return _game.Run();
}