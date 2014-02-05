#pragma once

#include "Scene.h"

class CSceneIntro : public CScene {

private:
	static CSceneIntro instance;
	CSceneIntro();

public:

	void loop();
	void init();
	void render();
	void on_event();
	void activate();
	void deactivate();
	inline static CSceneIntro* GetInstance() { return &instance; }

};

