#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>

class CResourceManager
{
public:
	CResourceManager(void);
	virtual ~CResourceManager(void);

	static SDL_Texture* load_texture(const std::string &file, SDL_Renderer *ren);

	static SDL_Texture* load_texture_from_rc(int res, SDL_Renderer *ren);
	static SDL_Surface* load_surface_from_rc(int res, SDL_Renderer *ren);
	static TTF_Font* load_font_from_rc(int res, int size);

	static void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);	
	static void render_resized_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

	static SDL_Texture* render_text(std::string message, TTF_Font* font, SDL_Color color, SDL_Renderer *ren);
	static SDL_Texture* render_text_wrapped(std::string message, Uint32 wrap, TTF_Font* font, 
                        SDL_Color color, SDL_Renderer *ren);
	
};

