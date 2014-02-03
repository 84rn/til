#include "App.h"

CApp::CApp()
{
	terminated = false;
}


CApp::~CApp()
{
}

int CApp::execute()
{
	if (!init())
	{
		return 1;
	}

	while (!terminated)
	{
		on_event();
		loop();
		render();
	}

	cleanup();

	return 0;

}

void CApp::cleanup()
{

}

bool CApp::init()
{
	return true;

}

void CApp::loop()
{

}

void CApp::on_event()
{

}

void CApp::render()
{

}

