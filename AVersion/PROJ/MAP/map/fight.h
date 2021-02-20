#ifndef _FIGHT_H_
#define _FIGHT_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"
#include "chosePokemon.h"
#include "pc.h"

int fightDisplay (Config config, Pokemon tab[6], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, MYSQL * mysql, MYSQL_ROW row, SDL_Renderer ** renderer, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv);
void closeFightDisplay (Pokemon tab[6], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv);
int managefight (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, MYSQL_ROW row);
int takePokemonUser (MYSQL * mysql, Pokemon * tab);
int takePokemonAdv (MYSQL * mysql, Pokemon * adv, int lvlPlaye, MYSQL_ROW row);
int loadDiplayPokemonAdv (SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, MYSQL_ROW row);
int loadDiplayPokemonPlayer (MYSQL * mysql, SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, Pokemon * pokemonActu);
int displayPvPokemon (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Color black, Pokemon pokemon, int x, int y, SDL_Renderer ** renderer, SDL_Rect * rectangle);
int displayChoseActionFight (SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer);
int updateDisplayChoseActionFight (SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, char poss, SDL_Renderer ** renderer);
int manageEventChoseActionFight (Config config, SDL_Surface ** surfacePokemonPlayer, int * actu, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText, Pokemon * adv, MYSQL * mysql, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, Pokemon pokemonPlayer[6], SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer);
int updateDisplayAtack (SDL_Rect * rectangleChoseAttack, SDL_Rect * rectangleCurseur, SDL_Rect rectangleAttack[4], SDL_Texture ** textureCurseur, SDL_Texture ** textureChoseAttack, Pokemon * pokemonPlayer, SDL_Renderer ** renderer);
int manageChoseAtack (Config config, SDL_Surface ** surfacePokemonPlayer, int actu, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText, Pokemon * adv, MYSQL * mysql, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, Pokemon pokemonPlayer[6], SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer);
int displayChoseAttack (SDL_Rect * rectangleChoseAttack, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur, SDL_Rect rectangleAttack[4], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, Pokemon * pokemonPlayer, SDL_Renderer ** renderer);
int actionAttack (MYSQL * mysql, int lvl, int attack, Attack selected, Pokemon * adv);
int updateFightDisplay (SDL_Surface ** surfacePokemonPlayer, MYSQL * mysql, Pokemon * player, Pokemon adv, SDL_Surface ** text, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText);
int finishFight (MYSQL * mysql, Pokemon * pokemonPlayer, int lvlAdv);
int takeComp (MYSQL * mysql, Pokemon * pokemon);
int takeTypes (MYSQL * mysql, Pokemon * pokemon);
int catchPokemon (Pokemon * adv, MYSQL * mysql);
int deleteItem (const char * item, MYSQL * mysql);

#endif
