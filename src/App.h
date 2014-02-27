#pragma once
#include "SDL/SDL.h"

class CApp {

public:

	CApp();
	~CApp();

	enum Error {
		NO_ERRORS = 0,
		INIT_ERROR
	};

	// Function starts the main app and returns the exit code
	int execute();

private:
	// Initialization
	bool init();
	// Function checks for events and passes them to scene manager
	void on_event();
	// App logic
	void loop();
	// Drawing to screen
	void render();
	// Used for cleaning up
	void cleanup();

	bool terminated;

	// Main window handle
	SDL_Window* win;
	// Renderer handle
	SDL_Renderer* ren;
	
};


