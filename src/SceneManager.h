#pragma once

#include <queue>
#include "Scene.h"
#include "SceneIntro.h"
#include "SceneMain.h"


class CSceneManager {

public:
	CSceneManager(void);
	~CSceneManager(void);

	enum Scenes {
		SCENE_NONE,
		SCENE_INTRO,
		SCENE_MAIN
	};

	static void activate_scene(Scenes scene);
	static void on_event(SDL_Event& event);
	static void loop();
	static void render();
	static bool check_scene_queue();

	static SDL_Window* get_main_window();	
	static void set_main_window(SDL_Window*);

	static SDL_Renderer* get_renderer();	
	static void set_renderer(SDL_Renderer*);

private:
	static CScene* scene;
	static std::queue<Scenes> scene_queue;

	static SDL_Window* main_window;
	static SDL_Renderer* renderer;

};

