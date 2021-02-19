#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"

int menuDisplay(SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int manageEventMenu (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Rect * rectanglePlayer, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur);
int updateMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur);
int manageMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer);
void closeMenuDisplay (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int loadDiplayMenu (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Renderer ** renderer, SDL_Rect * rectangleMenu);

#endif
