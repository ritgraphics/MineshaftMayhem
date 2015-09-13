
#include <vix_game.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <vix_font.h>

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
	ICamera3D*  m_camera3D;
	IModel*     m_floor;
	IFont*      m_font;
	Transform   floorTransform;
	Transform   fontTransform;
};

EndlessRunner::EndlessRunner()
	: IGame()
{

}

void EndlessRunner::VOnStartup()
{
	m_renderer->VSetClearColor(Vixen::Colors::Black);

	m_camera3D = m_renderer->Camera3D();
	m_camera3D->VSetSpeed(50.0f);

	m_floor = ResourceManager::OpenModel(VTEXT("floor.mdl"));
	m_font = ResourceManager::OpenFont(VTEXT("Consolas_24.fnt"));



	floorTransform = Transform(0.0f, -5.0f, 5.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f);
	fontTransform = Transform(20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	m_floor->VSetTransform(&floorTransform);

	m_window->VToggleCursor();
}

void EndlessRunner::VOnUpdate(float dt)
{
	if (m_keyboard->SingleKeyPress(IKEY::F2))
		m_window->VClose();

	if (m_keyboard->KeyPress(IKEY::S))
		m_camera3D->VWalk(-dt);

	if (m_keyboard->KeyPress(IKEY::W))
		m_camera3D->VWalk(dt);

	if (m_keyboard->KeyPress(IKEY::A))
		m_camera3D->VStrafe(-dt);

	if (m_keyboard->KeyPress(IKEY::D))
		m_camera3D->VStrafe(dt);


	int deltaX = m_mouse->DeltaX(m_window->VGetClientBounds().w / 2);
	int deltaY = m_mouse->DeltaY(m_window->VGetClientBounds().h / 2);
	m_camera3D->VRotateX(deltaY * 0.25f);
	m_camera3D->VRotateY(deltaX * 0.25f);

	m_camera3D->VUpdate(dt);

	m_window->VTrapCursorCenter();
}

void EndlessRunner::VOnRender(float dt)
{
	//m_renderer->VRenderModel(m_model);
	m_renderer->VRenderModel(m_floor);


	//ALL 2D UI IS DRAW AFTER SCENE IS DRAWN
	USStream ss;
	ss << "FPS: " << m_window->VFPS();
	m_renderer->VRenderText2D(m_font, ss.str(), fontTransform);
}

void EndlessRunner::VOnShutdown()
{
	
}



int main(int argc, char* argv[])
{
	EndlessRunner _game;

	return _game.Run();
}