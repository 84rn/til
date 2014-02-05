#include <iostream>
#include "SceneIntro.h"

CSceneIntro CSceneIntro::instance;

CSceneIntro::CSceneIntro() {

}


void CSceneIntro::loop() {

}


void CSceneIntro::init() {	

}


void CSceneIntro::render() {

}


void CSceneIntro::on_event() {

}


void CSceneIntro::activate() {

	std::cout << "Activating Intro Scene..." << std::endl;
	init();
}


void CSceneIntro::deactivate() {

	std::cout << "Deactivating Intro Scene..." << std::endl;

}
