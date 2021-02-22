#ifndef _MAINGAME_H_
#define _MAINGAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql/mysql.h>
#include "types.h"
#include "manage.h"
#include "home.h"
#include "menu.h"
#include "fight.h"

int matriceMain(int x, int y);
int mainGameDisplay (Config config, TTF_Font ** font, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, MYSQL * mysql);
int manageEventMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, MYSQL * mysql);
int updateMainGameDisplay (SDL_Renderer ** renderer, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int manageMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql);
void closeMainGameDisplay (SDL_Surface ** map, SDL_Texture ** texture, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer);
int randomAggro (Config config, TTF_Font ** font, SDL_Renderer ** renderer, int nextCase, MYSQL * mysql);
int randomChoseFight (Pokemon tab[6], Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, const char * type);

#endif
