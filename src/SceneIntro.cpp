#include <iostream>
#include "SDL/SDL.h"
#include "SceneIntro.h"
#include "SceneManager.h"

#define INTRO_INTERVAL_MS 4000

CSceneIntro CSceneIntro::instance;

Uint32 change_to_main_scene(Uint32 interval, void *param) {

	CSceneManager::activate_scene(CSceneManager::SCENE_MAIN);
	return 0;
}

CSceneIntro::CSceneIntro() {

}


void CSceneIntro::loop() {

}


void CSceneIntro::init() {	

	SDL_AddTimer(INTRO_INTERVAL_MS, change_to_main_scene, NULL);

}


void CSceneIntro::render() {

}


void CSceneIntro::on_event() {

}


void CSceneIntro::activate() {

	std::cout << "Activating Intro Scene..." << std::endl;
	init();
}


void CSceneIntro::deactivate() {

	std::cout << "Deactivating Intro Scene..." << std::endl;

}
