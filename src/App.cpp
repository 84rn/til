#include "App.h"
#include "SceneManager.h"

CApp::CApp() {

	terminated = false;
}

CApp::~CApp() {

}

int CApp::execute() {

	if (!init()) {
		return 1;
	}

	while (!terminated)	{
		on_event();
		loop();
		render();
	}

	cleanup();

	return 0;
}


void CApp::cleanup()
{

}

bool CApp::init()
{
	return true;

}

void CApp::loop()
{
	CSceneManager::loop();
}

void CApp::on_event()
{
	CSceneManager::on_event();
}

void CApp::render()
{
	CSceneManager::render();
}

