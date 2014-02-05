#pragma once

class CApp {

public:

	CApp();
	~CApp();

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
	
};


