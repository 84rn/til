#include <iostream>
#include "SceneMain.h"
#include "RedditFetcher.h"
#include "json/json.h"

CSceneMain CSceneMain::instance;

CSceneMain::CSceneMain() {

}


void CSceneMain::loop() {	

}


void CSceneMain::init() {

	CRedditFetcher fetcher("http://reddit.com/r/todayilearned.json");

	if (fetcher.fetch() == 0)
		std::cout << "OK" << std::endl;
	else
		std::cout << "ERROR" << std::endl;
}


void CSceneMain::render() {

}


void CSceneMain::on_event() {

}


void CSceneMain::activate() {

	std::cout << "Activating Main Scene..." << std::endl;
	init();
}


void CSceneMain::deactivate() {

	std::cout << "Deactivating Main Scene..." << std::endl;

}
