#ifndef _BUY_H_
#define _BUY_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"

int buyDisplay (SDL_Surface ** textPokedollard, SDL_Texture ** texturePokedollard, MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy);

int manageEventBuy (int pokeDollar, SDL_Texture ** texturePokeDollar, SDL_Rect * rectangle, int cost, MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectangleBuy);

int displayNumber (int cost, int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer);

int updateBuy (SDL_Texture ** texturePokeDollar, SDL_Rect * rectangle, int cost, int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectanglebuy);

int manageBuy (MYSQL * mysql, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer);

void closeBuy (SDL_Surface ** textPokedollard, SDL_Texture ** texturePokedollard, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy);

int buy (MYSQL * mysql, int cost, int number, int pokeDollar);

#endif
