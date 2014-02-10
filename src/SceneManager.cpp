#include "SceneManager.h"

CScene* CSceneManager::scene = 0;
std::queue<CSceneManager::Scenes> CSceneManager::sceneQueue;

CSceneManager::CSceneManager(void) {

}

CSceneManager::~CSceneManager(void) {

	 if (scene)
		scene->deactivate();

}

bool CSceneManager::check_scene_queue() {

	if (sceneQueue.empty())
		return false;
	else {
		Scenes scene_from_queue = sceneQueue.front();
		sceneQueue.pop();

		if (scene)
			scene->deactivate();

		switch (scene_from_queue) {
		case SCENE_NONE:
			scene = 0;
			break;
		case SCENE_INTRO:
			scene = CSceneIntro::get_instance();
			break;
		case SCENE_MAIN:
			scene = CSceneMain::get_instance();
			break;
		}

		if (scene)
			scene->activate();

		return true;
	}

}	

void CSceneManager::activate_scene(Scenes new_scene) {

	sceneQueue.push(new_scene);	
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



