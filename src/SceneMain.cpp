#include <iostream>
#include "SceneMain.h"

CSceneMain CSceneMain::instance;

CSceneMain::CSceneMain() {

}


void CSceneMain::loop() {

}


void CSceneMain::init() {



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
