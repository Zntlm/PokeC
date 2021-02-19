#ifndef _HOMEPAGE_H_
#define _HOMEPAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql/mysql.h>
#include "types.h"
#include "manage.h"
#include "config.h"
#include "mainGame.h"

int displayHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, SDL_Surface ** surfaceHomePage, SDL_Texture ** textureHomePage, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int manageEventHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, SDL_Rect * rectangleHomePage, SDL_Texture ** textureHomePage, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur);
int updateHomePage (SDL_Renderer ** renderer, SDL_Rect * rectangleHomePage, SDL_Texture ** textureHomePage, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur);
void closeHomePage (SDL_Surface ** surfaceHomePage, SDL_Texture ** textureHomePage, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int manageHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql);

#endif
