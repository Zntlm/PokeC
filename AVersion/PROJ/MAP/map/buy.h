#ifndef _BUY_H_
#define _BUY_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"

int buyDisplay (MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy);

int manageEventBuy (MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectangleBuy);

int displayNumber (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer);

int updateBuy (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectanglebuy);

int manageBuy (MYSQL * mysql, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer);

void closeBuy (SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy);


#endif
