#ifndef _CHOSEPOKEMON_H_
#define _CHOSEPOKEMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql/mysql.h>
#include "types.h"
#include "manage.h"
#include "fight.h"

void closeSwitchPokemon (SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch);
int switchDisplay (Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer);
int displaySixPokemon (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Rect rectangle[6], SDL_Surface ** surfacePokemon, SDL_Renderer ** renderer);
int manageSwitchPokemon (Config config, TTF_Font ** font, Pokemon player[6], SDL_Renderer ** renderer);
int manageSwitchPokemonDisplay (int number, Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer);
int updatePokeball (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer);

#endif
