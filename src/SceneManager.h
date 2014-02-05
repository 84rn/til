#pragma once

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

private:
	static CScene* scene;

};

