#pragma once
#include "SDL/SDL.h"

class CScene {

public:
	CScene();

	virtual void loop() = 0;
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void on_event(SDL_Event&) = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;

};

