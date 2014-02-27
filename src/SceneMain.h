#pragma once

#include "Scene.h"
#include "ThreadQueue.h"
#include <string>
#include "SDL/SDL_ttf.h"

class CSceneMain : public CScene {

private:
	static CSceneMain instance;
	CSceneMain();	
	
	std::vector<SDL_Texture*> textures;
	int current_texture;

	std::string current_text;
	std::string old_text;

	CThreadQueue<std::string> text_queue;

	// Windows w/h
	int width, height;
	TTF_Font* font;

	SDL_Thread* curl_thread;	

public:

	void loop();
	void init();
	void render();
	void on_event(SDL_Event&);
	void activate();
	void deactivate();
	void set_current_texture(int);
	void set_current_text(std::string);
	void run_curl_thread();	

	inline CThreadQueue<std::string>* get_queue() { return &text_queue; };

	inline static CSceneMain* get_instance() { return &instance; }

};

