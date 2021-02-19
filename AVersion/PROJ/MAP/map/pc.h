#ifndef _PC_H_
#define _PC_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"
#include "menu.h"
#include "home.h"
#include "buy.h"

int pcDisplay(MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseurPc, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion);
int loadDiplayCurseurPc (SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPc);
int loadDiplayPc (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc);
int updateMainPcDisplay (MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Texture ** texturePc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc, SDL_Rect * rectangleCurseurPc, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int manageEventPc (MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Rect * rectangleCurseurPc, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion);
int managePcDisplay (MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome);
void closePcDisplay (SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseur);
int displayItem (MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer);

#endif
