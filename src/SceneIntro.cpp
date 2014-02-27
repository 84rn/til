#include <iostream>
#include "SDL/SDL_image.h"
#include "SceneIntro.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "../rc/resource.h"

#define INTRO_INTERVAL_MS 2000

CSceneIntro CSceneIntro::instance;

Uint32 change_to_main_scene(Uint32 interval, void *param) {

	CSceneManager::activate_scene(CSceneManager::SCENE_MAIN);
	return 0;
}

CSceneIntro::CSceneIntro() : 	intro_img(NULL) {


}

void CSceneIntro::loop() {

}


void CSceneIntro::init() {	

	SDL_ShowCursor(0);

	intro_img = CResourceManager::load_texture_from_rc(IDR_INTRO_JPG, CSceneManager::get_renderer());

	if(!intro_img)
		return;

	Uint8 r, g, b;
	
	SDL_Surface *intro_surface =  CResourceManager::load_surface_from_rc(IDR_INTRO_JPG, CSceneManager::get_renderer());
	SDL_GetRGB((static_cast<Uint32*>(intro_surface->pixels))[0], intro_surface->format, &r, &g, &b);
	SDL_FreeSurface(intro_surface);
	intro_surface = NULL;	
	
	SDL_SetRenderDrawColor(CSceneManager::get_renderer(), r, g, b, 0);
	SDL_RenderClear(CSceneManager::get_renderer());

	SDL_AddTimer(INTRO_INTERVAL_MS, change_to_main_scene, NULL);

}


void CSceneIntro::render() {

	int w, h;
	SDL_Rect size;

	SDL_GetWindowSize(CSceneManager::get_main_window(), &w, &h);
	SDL_QueryTexture(intro_img, NULL, NULL, &size.w, &size.h);

	CResourceManager::render_texture(intro_img, CSceneManager::get_renderer(), w/2 - size.w/2, h/2 - size.h/2);

}


void CSceneIntro::on_event(SDL_Event& event) {

}


void CSceneIntro::activate() {

	std::cout << "Activating Intro Scene..." << std::endl;
	init();
}


void CSceneIntro::deactivate() {

	std::cout << "Deactivating Intro Scene..." << std::endl;

	if(intro_img) {
		SDL_DestroyTexture(intro_img);
		intro_img = NULL;
	}

	SDL_SetRenderDrawColor(CSceneManager::get_renderer(), 0, 0, 0, 0);

}
