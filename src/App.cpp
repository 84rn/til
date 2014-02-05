#include "App.h"
#include "SceneManager.h"

CApp::CApp() {

	terminated = false;
}

CApp::~CApp() {

}

int CApp::execute() {

	if (!init()) {
		return INIT_ERROR;
	}

	while (!terminated)	{
		on_event();
		loop();
		render();
	}

	cleanup();

	return NO_ERRORS;
}

void CApp::cleanup()
{
	CSceneManager::activate_scene(CSceneManager::SCENE_NONE);

}

bool CApp::init()
{
	CSceneManager::activate_scene(CSceneManager::SCENE_INTRO); 
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

