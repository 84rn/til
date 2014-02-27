#include "App.h"
#include "SceneManager.h"
#include "SDL/SDL_ttf.h"


CApp::CApp() : terminated(false), win(NULL), ren(NULL) {

}

CApp::~CApp() {

}

int CApp::execute() {

	if (!init()) {
		return Error::INIT_ERROR;
	}

	while (!terminated)	{
		CSceneManager::check_scene_queue();
		on_event();
		loop();
		render();
	}

	cleanup();

	return Error::NO_ERRORS;
}

void CApp::cleanup() {

	CSceneManager::activate_scene(CSceneManager::SCENE_NONE);
	CSceneManager::check_scene_queue();

	if(win) {
		SDL_DestroyWindow(win);
		win = NULL;

	}

	if(ren) {
		SDL_DestroyRenderer(ren);
		ren = NULL;
	}

	TTF_Quit();
	SDL_Quit();

}

bool CApp::init() {

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);

	if (TTF_Init() == -1)
		return false;
	
    win = SDL_CreateWindow("TIL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (win == NULL) {        
        return false;
    }
	
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {        
        return false;
    }

	CSceneManager::set_main_window(win);
	CSceneManager::set_renderer(ren);

	CSceneManager::activate_scene(CSceneManager::SCENE_INTRO); 
	return true;
}

void CApp::loop() {	

	CSceneManager::loop();
}

void CApp::on_event() {

	SDL_Event e;

	while (SDL_PollEvent(&e)){
		//If user closes he window
		if (e.type == SDL_QUIT)
			terminated = true;
		//If user presses any key
		if (e.type == SDL_KEYDOWN)
			if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				terminated = true;

	}

	CSceneManager::on_event(e);
}

void CApp::render() {

	CSceneManager::render();
}

