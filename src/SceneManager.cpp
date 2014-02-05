#include "SceneManager.h"

CScene* CSceneManager::scene = 0;

CSceneManager::CSceneManager(void) {

}

CSceneManager::~CSceneManager(void) {

	 if (scene)
		scene->deactivate();

}

void CSceneManager::activate_scene(Scenes new_scene) {

	if (scene)
		scene->deactivate();

	switch (new_scene) {
	case SCENE_NONE:
		scene = 0;
		break;
	case SCENE_INTRO:
		scene = CSceneIntro::GetInstance();		
		break;
	case SCENE_MAIN:
		scene = CSceneMain::GetInstance();
		break;
	}

	if (scene)
		scene->activate();
}

void CSceneManager::on_event() {

	if (scene) {
		scene->on_event();
	}

}

void CSceneManager::loop() {

	if (scene) {
		scene->loop();
	}

}

void CSceneManager::render() {

	if (scene) {
		scene->render();
	}

}



