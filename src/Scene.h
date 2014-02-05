#pragma once

class CScene {

public:
	CScene();

	virtual void loop() = 0;
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void on_event() = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;

};

