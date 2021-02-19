#ifndef _HOME_H_
#define _HOME_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"
#include "pc.h"
#include "menu.h"

int MatriceHome(int x, int y);
void closeHomeDisplay (SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int manageHomeDisplay (Config config, SDL_Renderer ** renderer, SDL_Texture ** texturePlayer);
int homeDisplay(SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int loadDiplayHome (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int updateMainHomeDisplay (SDL_Renderer ** renderer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int displayPlayerHome (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int manageEventHomeGame (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** texturePc, SDL_Rect * rectanglePc);

#endif
