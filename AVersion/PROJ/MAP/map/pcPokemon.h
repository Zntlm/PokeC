#ifndef _PCPOKEMON_H_
#define _PCPOKEMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"
#include "chosePokemon.h"

int displayPc (SDL_Texture ** textureText, SDL_Surface ** text, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int managePc (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, MYSQL * mysql, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int number, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, Config config, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer);
int updatePc (Pokemon pokemon, TTF_Font ** font, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int min, int max, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer);
int managePcPokemon (MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer);
void closePcPokemon (SDL_Texture ** textureText, SDL_Surface ** text, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int selectPokemon (int * number, MYSQL * mysql, Pokemon ** listPokemon);
int displayPokemon (SDL_Surface ** surfacePokemon, int min, int max, Pokemon ** listPokemon, SDL_Renderer ** renderer);
int updatePcMenu (SDL_Texture ** textureMenu, SDL_Rect * rectangleMenu, SDL_Texture ** textureCurseurMenu, SDL_Rect * rectangleCurseurMenu, SDL_Renderer ** renderer);
int managePcMenu (TTF_Font ** font, MYSQL * mysql, Pokemon * selected, Config config, SDL_Texture ** textureMenu, SDL_Rect * rectangleMenu, SDL_Texture ** textureCurseurMenu, SDL_Rect * rectangleCurseurMenu, SDL_Renderer ** renderer);
int displayChoseAction (TTF_Font ** font, MYSQL * mysql, Pokemon * selected, Config config, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Renderer ** renderer);
int displayChangePokemon (Pokemon * selected, TTF_Font ** font, Config config, SDL_Renderer ** renderer, MYSQL * mysql, Pokemon tab[6]);
int changePokemon (MYSQL * mysql, Pokemon sac, Pokemon * selected);
int manageChangePokemon (Pokemon * selected, TTF_Font ** font, Config config, SDL_Renderer ** renderer, MYSQL * mysql);
int displayStats (Pokemon pokemon, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** text, SDL_Texture ** textureText);

#endif
