#pragma once

#include "Scene.h"
#include "SDL/SDL.h"

class CSceneIntro : public CScene {

private:
	static CSceneIntro instance;
	CSceneIntro();
	SDL_Texture* intro_img;

public:

	void loop();
	void init();
	void render();
	void on_event(SDL_Event&);
	void activate();
	void deactivate();
	inline static CSceneIntro* get_instance() { return &instance; } 



};

