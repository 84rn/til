#pragma once

#include "Scene.h"

class CSceneMain : public CScene {

private:
	static CSceneMain instance;
	CSceneMain();

public:

	void loop();
	void init();
	void render();
	void on_event();
	void activate();
	void deactivate();
	inline static CSceneMain* get_instance() { return &instance; }

};

