#include "ResourceManager.h"
#include "windows.h"
#include "../rc/resource.h"

CResourceManager::CResourceManager(void) {
}


CResourceManager::~CResourceManager(void) {
}


TTF_Font* CResourceManager::load_font_from_rc(int res, int size) {
	
	HRSRC font_resource = FindResource(NULL, MAKEINTRESOURCE(res), RT_RCDATA);

    unsigned int resource_size = SizeofResource(NULL, font_resource);
    HGLOBAL resource_data = LoadResource(NULL, font_resource);
    void* resource_data_pointer = LockResource(resource_data);	

	SDL_RWops *rw;
	rw = SDL_RWFromMem(resource_data_pointer, resource_size);

	TTF_Font* font = NULL;
	font = TTF_OpenFontRW(rw, 1, size);		

	UnlockResource(resource_data);
	
	return font;
}

SDL_Texture* CResourceManager::render_text(std::string message, TTF_Font* font, 
                        SDL_Color color, SDL_Renderer *ren)
{	   
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);	

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);

    SDL_FreeSurface(surf);

    return texture;
}


SDL_Texture* CResourceManager::render_text_wrapped(std::string message, Uint32 wrap, TTF_Font* font, 
                        SDL_Color color, SDL_Renderer *ren)
{	   
	SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(font, message.c_str(), color, wrap);	

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);

    SDL_FreeSurface(surf);

    return texture;
}

SDL_Texture* CResourceManager::load_texture(const std::string &file, SDL_Renderer *ren) {

	SDL_Texture *texture = NULL;	
	SDL_Surface *loaded_image = IMG_Load(file.c_str());

	if (loaded_image != NULL) {
		texture = SDL_CreateTextureFromSurface(ren, loaded_image);
		SDL_FreeSurface(loaded_image);		
	}

	return texture;
}


SDL_Surface* CResourceManager::load_surface_from_rc(int res, SDL_Renderer *ren) {

	HRSRC img_resource = FindResource(NULL, MAKEINTRESOURCE(res), RT_RCDATA);

    unsigned int resource_size = SizeofResource(NULL, img_resource);
    HGLOBAL resource_data = LoadResource(NULL, img_resource);
    void* resource_data_pointer = LockResource(resource_data);

	SDL_RWops *rw;
	rw = SDL_RWFromMem(resource_data_pointer, resource_size);

	SDL_Surface* loaded_image = IMG_Load_RW(rw, 0);

	SDL_FreeRW(rw);
	UnlockResource(resource_data);

	return loaded_image;
}

SDL_Texture* CResourceManager::load_texture_from_rc(int res, SDL_Renderer *ren) {

	HRSRC img_resource = FindResource(NULL, MAKEINTRESOURCE(res), RT_RCDATA);

    unsigned int resource_size = SizeofResource(NULL, img_resource);
    HGLOBAL resource_data = LoadResource(NULL, img_resource);
    void* resource_data_pointer = LockResource(resource_data);

	SDL_RWops *rw;
	rw = SDL_RWFromMem(resource_data_pointer, resource_size);

	SDL_Texture* texture = NULL;	
	SDL_Surface* loaded_image = IMG_Load_RW(rw, 0);

	if (loaded_image != NULL) {
		texture = SDL_CreateTextureFromSurface(ren, loaded_image);
		SDL_FreeSurface(loaded_image);	
	}
	
	SDL_FreeRW(rw);
	UnlockResource(resource_data);

	return texture;
}

void CResourceManager::render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


void CResourceManager::render_resized_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dst);
}