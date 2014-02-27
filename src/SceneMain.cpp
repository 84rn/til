#include <iostream>
#include "SceneMain.h"
#include "RedditFetcher.h"
#include "json/json.h"
#include "SDL/SDL_image.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "../rc/resource.h"
#include "SDL/SDL_ttf.h"
#include <cstdlib>

#define DEFAULT_MAIN_INTERVAL 15000
#define FONT_SIZE 82

CSceneMain CSceneMain::instance;


Uint32 change_text(Uint32 interval, void *param) {

	srand(static_cast<unsigned int>(time(NULL)));

	CSceneMain* scene = static_cast<CSceneMain*>(param);

	scene->set_current_texture(rand() % 6);

	if(scene->get_queue()->empty()) {
		scene->set_current_text("Loading...");
		return 2000;
	}
	else
	{
		std::string new_text = scene->get_queue()->pop();
		scene->set_current_text(new_text);
		std::cout << "Set current text to: " << new_text << std::endl;
	}

	if(scene->get_queue()->size() < 5)
		scene->run_curl_thread();

	return DEFAULT_MAIN_INTERVAL;
}



CSceneMain::CSceneMain() : curl_thread(NULL), font(NULL) {

}


void CSceneMain::loop() {	

}


void CSceneMain::set_current_texture(int ix) {
	current_texture = ix;
}


void CSceneMain::set_current_text(std::string str) {

	current_text = str;
}

void CSceneMain::init() {	
	
	run_curl_thread();

	SDL_GetWindowSize(CSceneManager::get_main_window(), &width, &height);

	for(int i = 0; i < 6; i++) {
		SDL_Texture* tex = CResourceManager::load_texture_from_rc(IDR_TAP0 + i, CSceneManager::get_renderer());
		textures.push_back(tex);
	}

	font = CResourceManager::load_font_from_rc(IDR_FONT, FONT_SIZE);  


	std::cout << "Loaded font " << TTF_FontFaceFamilyName(font) << " of size: " << TTF_FontHeight(font) << std::endl;	

	//SDL_RenderClear(CSceneManager::get_renderer());

	SDL_AddTimer(0, change_text, this);
	SDL_Delay(100);
/*
	CRedditFetcher fetcher("http://reddit.com/r/todayilearned.json");

	if (fetcher.fetch() == 0)
		std::cout << "OK" << std::endl;
	else
		std::cout << "ERROR" << std::endl;*/

}


void CSceneMain::render() {		

	if(old_text != current_text) {
		
		CResourceManager::render_texture(textures[current_texture], CSceneManager::get_renderer(), 0, 0);

		SDL_Color color = {255, 255, 255};
		SDL_Texture* text = CResourceManager::render_text_wrapped(current_text, static_cast<Uint32>(0.8 * width), font, color, CSceneManager::get_renderer());
		int w, h;
		SDL_QueryTexture(text, NULL, NULL, &w, &h);

		CResourceManager::render_texture(text, CSceneManager::get_renderer(), width/2 - w/2, height/2 - h/2);
		SDL_DestroyTexture(text);

		old_text = current_text;
	}
}


void CSceneMain::on_event(SDL_Event& event) {

}


void CSceneMain::activate() {

	std::cout << "Activating Main Scene..." << std::endl;
	init();
}


void CSceneMain::deactivate() {

	std::cout << "Deactivating Main Scene..." << std::endl;

	for(std::vector<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); it++) {
		if(*it != NULL)
			SDL_DestroyTexture(*it);
	}

	if(font)
		TTF_CloseFont(font);
		
}

int get_til_data(void *ptr)
{
    CThreadQueue<std::string>* queue = static_cast<CThreadQueue<std::string>* >(ptr);

	static CRedditFetcher fetcher("http://reddit.com/r/todayilearned.json");

	if (fetcher.fetch() == 0)
		std::cout << "Fetch OK" << std::endl;
	else
		std::cout << "Fetch ERROR" << std::endl;

	Json::Value root; 
	Json::Reader reader;
	std::string page;
	page << fetcher;

	bool parsing_successful = reader.parse(page, root);
	if(parsing_successful) {
		Json::Value data = root["data"]["children"];

		for(Json::Value::iterator it = data.begin(); data.end() != it; it++) {

			std::string text = (*it)["data"]["title"].asString();

			std::size_t pos = text.find("TIL that ");
			if(pos != std::string::npos)
			{
				text.replace(pos, 9, "");
			}
			pos = text.find("TIL ");
			if(pos != std::string::npos)
			{
				text.replace(pos, 4, "");
			}
			pos = text.find("TIL: ");
			if(pos != std::string::npos)
			{
				text.replace(pos, 5, "");
			}

			text[0] = toupper(text[0]);

			queue->push(text);
		}


	}

    return 0;
}


void CSceneMain::run_curl_thread() {

	int ret;
	if(curl_thread)
		SDL_WaitThread(curl_thread, &ret);


	curl_thread = SDL_CreateThread(get_til_data, "TILThread", (void*)get_queue());

}