#include "SceneManager.h"

CScene* CSceneManager::scene = NULL;
std::queue<CSceneManager::Scenes> CSceneManager::scene_queue;
SDL_Window* CSceneManager::main_window = NULL;
SDL_Renderer* CSceneManager::renderer = NULL;

CSceneManager::CSceneManager(void) {


}

CSceneManager::~CSceneManager(void) {

	 if (scene)
		scene->deactivate();
}

SDL_Window* CSceneManager::get_main_window() {
	return main_window;
}

SDL_Renderer* CSceneManager::get_renderer() {
	return renderer;
}

void CSceneManager::set_main_window(SDL_Window* new_window) {
	main_window = new_window;
}

void CSceneManager::set_renderer(SDL_Renderer* new_renderer) {
	renderer = new_renderer;
}

bool CSceneManager::check_scene_queue() {

	if (scene_queue.empty())
		return false;
	else {
		Scenes scene_from_queue = scene_queue.front();
		scene_queue.pop();

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
	
	scene_queue.push(new_scene);	
}

void CSceneManager::on_event(SDL_Event& event) {

	if (scene) {
		scene->on_event(event);
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

	SDL_RenderPresent(renderer);

}



