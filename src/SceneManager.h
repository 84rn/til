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
	static void on_event();
	static void loop();
	static void render();
	static bool check_scene_queue();

private:
	static CScene* scene;
	static std::queue<Scenes> sceneQueue;

};

