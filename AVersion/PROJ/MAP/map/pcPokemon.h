#ifndef _PCPOKEMON_H_
#define _PCPOKEMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"

int displayPc (SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int managePc (SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int number, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, Config config, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer);
int updatePc (SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int min, int max, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer);
int managePcPokemon (MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer);
void closePcPokemon (SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int selectPokemon (int * number, MYSQL * mysql, Pokemon ** listPokemon);
int displayPokemon (SDL_Surface ** surfacePokemon, int min, int max, Pokemon ** listPokemon, SDL_Renderer ** renderer);

#endif
