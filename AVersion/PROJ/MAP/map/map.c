#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql/mysql.h>

/********************************************
*******************TYPE DEF******************
********************************************/

typedef struct Attack {

	char name[100];
	char type[50];
	int Power;
	int Acc;
	int lvl;
	SDL_Texture * text;

} Attack;

typedef struct Pokemon {

	char name[100];
	char type[2][50];
	int pv;
	int pvActuel;
	int attack;
	int defense;
	int speed;
	int lvl;
	char id[256];
	int xp;
	Attack comp[4];
	SDL_Texture * img;

} Pokemon;

typedef struct Config {

	int escape;
	int validate;
	int cancel;
	int up;
	int down;
	int right;
	int left;
	int inventory;

} Config;

/********************************************
******************FONCTIONS******************
********************************************/

// manage error
void SDL_PrintError (const char * message);
void TTF_PrintError(const char * message);
void MySQL_PrintError (const char * message, MYSQL mysql);
void version ();
int connectDataBase (MYSQL * mysql);
int initSDL ();
int createWindow (SDL_Window ** window, int x, int y);
int createRenderer (SDL_Renderer ** renderer, SDL_Window ** window);
int loadBMP (const char * img, SDL_Surface ** surface);
int createTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Surface ** surface);
int loadTexture (SDL_Texture ** texture, SDL_Rect * rectangle);
int updateRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle);
int loadFont (TTF_Font ** font);
int displayAll (SDL_Texture ** texture, SDL_Surface ** surface, SDL_Rect * rectangle, SDL_Renderer ** renderer, int x, int y, int w, int h);

// main game
int matriceMain(int x, int y);
int mainGameDisplay (Config config, TTF_Font ** font, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, MYSQL * mysql);
int manageEventMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, MYSQL * mysql);
int updateMainGateDisplay (SDL_Renderer ** renderer, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int manageMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql);
void closeMainGameDisplay (SDL_Surface ** map, SDL_Texture ** texture, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer);
int randomAggro (Config config, TTF_Font ** font, SDL_Renderer ** renderer, int nextCase, MYSQL * mysql);
int randomChoseFight (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, const char * type);

// menu
int menuDisplay(SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int manageEventMenu (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Rect * rectanglePlayer, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur);
int updateMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur);
int manageMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer);
void closeMenuDisplay (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int loadDiplayMenu (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Renderer ** renderer, SDL_Rect * rectangleMenu);

// Home
int MatriceHome(int x, int y);
void closeHomeDisplay (SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int manageHomeDisplay (Config config, SDL_Renderer ** renderer, SDL_Texture ** texturePlayer);
int homeDisplay(SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int loadDiplayHome (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int updateMainHomeDisplay (SDL_Renderer ** renderer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int displayPlayerHome (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int manageEventHomeGame (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** texturePc, SDL_Rect * rectanglePc);

//PC
int pcDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int loadDiplayCurseurPc (SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPc);
int loadDiplayPc (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc);
int updateMainPcDisplay (SDL_Texture ** texturePc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc, SDL_Rect * rectangleCurseurPc);
int manageEventPc (SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Rect * rectangleCurseurPc);
int managePcDisplay (SDL_Renderer ** renderer);
void closePcDisplay (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseur);


// Fight
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

// CHOSE POKEMON
void closeSwitchPokemon (SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch);
int switchDisplay (Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer);
int displaySixPokemon (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Rect rectangle[6], SDL_Surface ** surfacePokemon, SDL_Renderer ** renderer);
int manageSwitchPokemon (Config config, TTF_Font ** font, Pokemon player[6], SDL_Renderer ** renderer);
int manageSwitchPokemonDisplay (Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer);
int updatePokeball (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer);

// HOME PAGE
int displayHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, SDL_Surface ** surfaceHomePage, SDL_Texture ** textureHomePage, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int manageEventHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, SDL_Rect * rectangleHomePage, SDL_Texture ** textureHomePage, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur);
int updateHomePage (SDL_Renderer ** renderer, SDL_Rect * rectangleHomePage, SDL_Texture ** textureHomePage, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur);
void closeHomePage (SDL_Surface ** surfaceHomePage, SDL_Texture ** textureHomePage, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur);
int manageHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql);

// CONFIG
int configKey (Config * config, SDL_Renderer ** renderer);
int defineKey (Config * config, SDL_Texture ** texture, SDL_Surface ** page, SDL_Renderer ** renderer);
int pressedKey ();
int manageDefineKey (Config * config, SDL_Renderer ** renderer);
void closeDefineKey (SDL_Texture ** texture, SDL_Surface ** page);

/********************************************
*********************MAIN********************
********************************************/

int main(int argc, char ** argv){

  SDL_Window * window = NULL;
  SDL_Renderer * renderer = NULL;
  SDL_bool programLaunched = SDL_TRUE;
  TTF_Font * font = NULL;
  MYSQL mysql;
  int nextCase;
	Config config;

  // init MySQL and connect database
  if (connectDataBase(&mysql))
    return 0;

  // start SDL
  if (initSDL())
    return 0;

  // create Window
  if (createWindow(&window, 1600, 900))
    return 0;

  // createRenderer
  if (createRenderer(&renderer, &window))
    return 0;

  if (loadFont(&font))
    return 0;

	if (configKey (&config, &renderer))
		return 0;

  manageHomePage (&config, &font, &renderer, &mysql);

  TTF_CloseFont (font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit ();
  TTF_Quit();
  mysql_close(&mysql);

  return 0;
}

/********************************************
*******************MAIN GAME*****************
********************************************/
// matrive map
int matriceMain(int x, int y){

  int MatriceMap[29][50]={
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                          {0, 0, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 3, 2, 3, 3, 3, 1, 1, 1, 1, 3, 0, 0, 0, 0, 5, 5, 5, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 3, 3, 3, 0, 0, 3, 3, 3, 1, 3, 3, 3, 5, 5, 5, 5, 5, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                          {0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 1, 1, 1, 3, 5, 5, 5, 5, 5, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
                          {0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 1, 3, 5, 5, 5, 5, 5, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 0, 0, 0, 0, 5, 0},
                          {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 1, 1, 1, 1, 3, 3, 3, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 3, 3, 3, 3, 3, 1, 3, 3, 3, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 3, 3, 3, 3, 3, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 5, 5, 1, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 3, 3, 3, 3, 3, 1, 3, 3, 0, 0, 1, 1, 0, 0, 0, 5, 5, 1, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 3, 3, 3, 3, 1, 0, 3, 0, 0, 0, 4, 4, 1, 5, 5, 5, 1, 5, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4, 1, 0},
                          {0, 5, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 4, 5, 5, 0, 1, 5, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 0, 0, 0, 0, 1, 1, 1, 0, 0, 5, 1, 1, 1, 1, 2, 4, 0, 0, 1, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 1, 1, 1, 1, 0, 4, 4, 4, 1, 1, 5, 5, 5, 5, 5, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 5, 1, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 5, 1, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 5, 1, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 0},
                          {0, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 5, 1, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
                          {0, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 1, 5, 5, 5, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 1, 5, 5, 5, 5, 1, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 5, 5, 5, 1, 5, 5, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 1, 5, 5, 5, 5, 1, 5, 5, 5, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 5, 5, 5, 1, 5, 5, 5, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
                          {0, 5, 1, 5, 5, 5, 5, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 5, 5, 1, 5, 5, 5, 5, 1, 5, 5, 5, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0},
                          {0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}
                        };

  return MatriceMap[y/32][x/32];
}

// init display map
int mainGameDisplay (Config config, TTF_Font ** font, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, MYSQL * mysql) {

  SDL_Rect rectangle;
  SDL_Rect rectanglePlayer;

  // load personnage texture
  if (loadBMP("../img/map.bmp", map))
    return 1;

  if (displayAll(texture, map, &rectangle, renderer, 0, 0, -1, -1))
    return 1;

  // load personnage texture
  if (loadBMP("../img/player.bmp", surfacePlayer))
    return 1;

  if (displayAll(texturePlayer, surfacePlayer, &rectanglePlayer, renderer, 32 * 3, 32 * 3, -1, -1))
    return 1;

  if (manageEventMainGame(config, font, renderer, map,  texture, &rectangle, surfacePlayer, texturePlayer, &rectanglePlayer, mysql))
    return 1;

  return 0;
}

// manage event in map
int manageEventMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, MYSQL * mysql) {

  SDL_bool programLaunched = SDL_TRUE;
  int nextCase;

  // event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						nextCase = matriceMain((*rectanglePlayer).x, (*rectanglePlayer).y-32);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).y -= 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.down) {

						nextCase = matriceMain((*rectanglePlayer).x, (*rectanglePlayer).y+32);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).y += 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.right) {

						nextCase = matriceMain((*rectanglePlayer).x+32, (*rectanglePlayer).y);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).x += 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.left) {

						nextCase = matriceMain((*rectanglePlayer).x-32, (*rectanglePlayer).y);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).x -= 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.inventory) {

						if (manageMenuDisplay (texture, texturePlayer, renderer, rectangle, rectanglePlayer))
							return 1;

					}

					if (updateMainGateDisplay (renderer, texture, rectangle, texturePlayer, rectanglePlayer))
						return 1;

          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }
    }
  }
  return 0;
}

// rendom attack by wild pokemon
int randomAggro (Config config, TTF_Font ** font, SDL_Renderer ** renderer, int nextCase, MYSQL * mysql) {

  int numRand;

  srand(time(NULL));
  numRand = rand()%2;

  if(!numRand) {

    switch (nextCase) {
      case 3:
        if (randomChoseFight (config, font, renderer, mysql, "Roche"))
		return 1;
        break;

      case 4:
        if (randomChoseFight (config, font, renderer, mysql, "Eau"))
		return 1;
        break;

      case 5:
        if (randomChoseFight (config, font, renderer, mysql, "Plante"))
		return 1;
        break;

      default:
        break;
    }
  }

  return 0;
}

// random chose wild pokemon
int randomChoseFight (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, const char * type) {

	int numRow;
	char * request;
	MYSQL_ROW row;
	MYSQL_RES * result;

	request = malloc(strlen("SELECT NamePokemon FROM BELONGSTO WHERE NameType=''") + strlen(type) + 1);
	strcpy(request, "SELECT NamePokemon FROM BELONGSTO WHERE NameType='");
	strcat(request, type);
	strcat(request, "'");

	if (mysql_query(mysql, request)) {
		free (request);
		return 1;
	}

	result = mysql_store_result(mysql);
  if (result == NULL) {
    MySQL_PrintError("Error extract résult", *mysql);
		return 1;
  }

	numRow = rand() % mysql_num_rows(result);

	for (int i = 0; i < numRow+1; i++) {
		row = mysql_fetch_row(result);
	}

	if (managefight(config, font, renderer, mysql, row))
		return 1;

	return 0;
}

// refresh map display
int updateMainGateDisplay (SDL_Renderer ** renderer, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(texture, renderer, rectangle))
    return 1;

  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;

  return 0;
}

// manage error in homeDisplay
int manageMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql) {

  SDL_Surface * map = NULL;
  SDL_Surface * surfacePlayer = NULL;
  SDL_Texture * texture = NULL;
  SDL_Texture * texturePlayer = NULL;

  int main = mainGameDisplay(config, font, &surfacePlayer, &texturePlayer, renderer, &map, &texture, mysql);
  closeMainGameDisplay(&map, &texture, &surfacePlayer, &texturePlayer);

  return main;
}

// free surface and texture used in menu
void closeMainGameDisplay (SDL_Surface ** map, SDL_Texture ** texture, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer) {
  if (*map != NULL)
    SDL_FreeSurface(*map);
  if (*texture != NULL)
    SDL_DestroyTexture(*texture);
  if (*surfacePlayer != NULL)
    SDL_FreeSurface(*surfacePlayer);
  if (*texturePlayer != NULL)
    SDL_DestroyTexture(*texturePlayer);
}

/********************************************
********************FIGHT********************
********************************************/

// init fight display
int fightDisplay (Config config, Pokemon tab[6], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, MYSQL * mysql, MYSQL_ROW row, SDL_Renderer ** renderer, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv) {

	Pokemon adv;
	int actu = 0;
	char  * request;
	SDL_Rect rectangleBackground;
	SDL_Rect rectanglePokemonPlayer;
	SDL_Rect rectanglePokemonAdv;
	SDL_Rect rectangleChoseActionFight;
	SDL_Rect rectangleCurseur;
	SDL_Rect rectangle;
	SDL_Color black = {0, 0, 0};

	if (takePokemonUser(mysql, tab))
		return 1;

	if (takePokemonAdv(mysql, &adv, tab[0].lvl, row))
		return 1;

	if (loadBMP("../img/background.bmp", surfaceBackground))
		return 1;

	if (displayAll(textureBackground, surfaceBackground, &rectangleBackground, renderer, 0, 0, -1, -1))
		return 1;

	if (loadDiplayPokemonAdv(surfacePokemonAdv, texturePokemonAdv, renderer, &rectanglePokemonAdv, row))
		return 1;

	if (loadDiplayPokemonPlayer(mysql, surfacePokemonPlayer, texturePokemonPlayer, renderer, &rectanglePokemonPlayer, &(tab[actu])))
		return 1;

	if (displayPvPokemon (text, textureText, font, black, tab[actu], 100, 0, renderer, &rectangle))
		return 1;

	if (displayPvPokemon (text, textureText, font, black, adv, 1100, 0, renderer, &rectangle))
		return 1;

	if (displayChoseActionFight(surfaceChoseActionFight, textureChoseActionFight, &rectangleChoseActionFight, surfaceCurseur, textureCurseur, &rectangleCurseur, renderer))
		return 1;

	if (manageEventChoseActionFight (config, surfacePokemonPlayer, &actu, &rectanglePokemonPlayer, &rectanglePokemonAdv, &rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText, &adv, mysql, text, font, black, surfaceChoseAttack, textureChoseAttack, tab, surfaceSelect, textureSelect, textureChoseActionFight, &rectangleChoseActionFight, textureCurseur, &rectangleCurseur, renderer))
		return 1;

	return 0;
}

// refresh fight display
int updateFightDisplay (SDL_Surface ** surfacePokemonPlayer, MYSQL * mysql, Pokemon * player, Pokemon adv, SDL_Surface ** text, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText) {

	SDL_Color black = {0, 0, 0};
	SDL_Rect rectangle;

	if (updateRenderer(textureBackground, renderer, rectangleBackground))
		return 1;

	if (updateRenderer(texturePokemonAdv, renderer, rectanglePokemonAdv))
		return 1;

	if ((*player).img != NULL) {
		if (updateRenderer(&((*player).img), renderer, rectanglePokemonPlayer))
			return 1;
	} else {
		if (loadDiplayPokemonPlayer(mysql, surfacePokemonPlayer, &((*player).img), renderer, rectanglePokemonPlayer, player))
			return 1;
	}

	if (displayPvPokemon (text, textureText, font, black, *player, 100, 0, renderer, &rectangle))
		return 1;

	if (displayPvPokemon (text, textureText, font, black, adv, 1100, 0, renderer, &rectangle))
		return 1;

	return 0;
}

// manage event in chose action fight
int manageEventChoseActionFight (Config config, SDL_Surface ** surfacePokemonPlayer, int * actu, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText, Pokemon * adv, MYSQL * mysql, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, Pokemon pokemonPlayer[6], SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer) {

	int curseur = 0;
	int action = 0;
	int tmp = 0;
	int i = 0;
	char poss = 0;
	SDL_bool programLaunched = SDL_TRUE;
	// event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						poss += (poss - 2 < 0)?2:-2;

					} else if (event.key.keysym.sym == config.down) {

						poss += (poss + 2 > 3)?-2:2;

					} else if (event.key.keysym.sym == config.right) {

						poss += (poss + 1 > 3)?-3:1;

					} else if (event.key.keysym.sym == config.left) {

						poss += (poss - 1 < 0)?3:-1;

					} else if (event.key.keysym.sym == config.validate) {

						switch (poss) {
							case 0: // fight
								action = 1;
								if (manageChoseAtack (config, surfacePokemonPlayer, *actu, rectanglePokemonPlayer, rectanglePokemonAdv, rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText, adv, mysql, text, font, black, surfaceChoseAttack, textureChoseAttack, pokemonPlayer, textureCurseur, rectangleCurseur, renderer))
									return 1;
								if ((*adv).pvActuel <= 0)
									return finishFight(mysql, &(pokemonPlayer[*actu]), (*adv).lvl);
								break;

							case 1: // pokemon
								do {
									tmp = manageSwitchPokemon (config, font, pokemonPlayer, renderer);
									if (tmp == 1)
										return 1;
								} while (pokemonPlayer[tmp % 10].pvActuel == 0);

								*actu = tmp % 10;
								action = 1;

								break;

							case 2: // item
								action = 1;
								break;

							case 3: // run
								return 0;
								break;
						}
					}

					if (action == 1){
						if (actionAttack (mysql, (*adv).lvl, (*adv).attack, (*adv).comp[rand()%4], &(pokemonPlayer[*actu])))
							return 1;
					}

					for (i = 0; i < 6 && pokemonPlayer[i].pvActuel <= 0; i++);
					if (i == 6)
						return 0;

					if (pokemonPlayer[*actu].pvActuel == 0) {
						do {
							tmp = manageSwitchPokemon (config, font, pokemonPlayer, renderer);
							if (tmp == 1)
								return 1;
						} while (pokemonPlayer[tmp % 10].pvActuel == 0);
						*actu = tmp % 10;
					}

					if (updateFightDisplay (surfacePokemonPlayer, mysql, &(pokemonPlayer[*actu]), *adv, text, font, renderer, rectanglePokemonPlayer, rectanglePokemonAdv, rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText))
						return 1;
					action = 0;
					if (updateDisplayChoseActionFight (textureChoseActionFight, rectangleChoseActionFight, textureCurseur, rectangleCurseur, poss, renderer))
						return 1;
          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }

    }
  }
	return 0;
}

// player win fight
int finishFight (MYSQL * mysql, Pokemon * pokemonPlayer, int lvlAdv) {

	char * request;

	(*pokemonPlayer).xp += lvlAdv;

	while ((*pokemonPlayer).xp > (*pokemonPlayer).lvl)
		(*pokemonPlayer).xp -= ++(*pokemonPlayer).lvl;

	request = malloc(strlen("UPDATE POKEBALL SET LVL= ,XP= WHERE ID=") + strlen((*pokemonPlayer).id) + sizeof(int) * 2 + 1);
	sprintf(request, "UPDATE POKEBALL SET LVL=%d ,XP=%d WHERE ID=%s", (*pokemonPlayer).lvl, (*pokemonPlayer).xp, (*pokemonPlayer).id);

	if (mysql_query(mysql, request)){
		free(request);
    MySQL_PrintError("Error query", *mysql);
    return 1;
	}
	free(request);

	return 0;
}

// mange event in attack menu
int manageChoseAtack (Config config, SDL_Surface ** surfacePokemonPlayer, int actu, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText, Pokemon * adv, MYSQL * mysql, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, Pokemon pokemonPlayer[6], SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer) {

	SDL_bool programLaunched = SDL_TRUE;
	SDL_Rect rectangleChoseAttack;
	SDL_Rect rectangleAttack[4];
	SDL_Rect rectangle;

	(*rectangleCurseur).x = 475;
	(*rectangleCurseur).y = 575;

	if (displayChoseAttack (&rectangleChoseAttack, rectangleCurseur, textureCurseur, rectangleAttack, surfaceChoseAttack, textureChoseAttack, text, font, black, &(pokemonPlayer[actu]), renderer))
		return 1;

	// event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						(*rectangleCurseur).y -= ((*rectangleCurseur).y == 575) ? - (3 * 75) : 75;

					} else if (event.key.keysym.sym == config.down) {

						(*rectangleCurseur).y += ((*rectangleCurseur).y == 575 + 3 * 75) ? - (3 * 75) : 75;

					} else if (event.key.keysym.sym == config.validate) {

						if (actionAttack(mysql, (pokemonPlayer[actu]).lvl, (pokemonPlayer[actu]).attack, (pokemonPlayer[actu]).comp[((*rectangleCurseur).y - 575) / 75], adv))
							return 1;
						return updateFightDisplay (surfacePokemonPlayer, mysql, &(pokemonPlayer[actu]), *adv, text, font, renderer, rectanglePokemonPlayer, rectanglePokemonAdv, rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText);

					}
	  			if (updateDisplayAtack (&rectangleChoseAttack, rectangleCurseur, rectangleAttack, textureCurseur, textureChoseAttack, &(pokemonPlayer[actu]), renderer))
						return 1;
          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }

    }
  }
	return 0;
}

// use attack
int actionAttack (MYSQL * mysql, int lvl, int attack, Attack selected, Pokemon * adv) {

	int numRand;
	MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;
	int power = selected.Power * lvl;

	if (attack < (*adv).defense) {
		power /= 2;
	}

	numRand = rand()%100;

	if (selected.Acc < numRand) {
		return 0;
	}

	for (int i = 0; i < 2; i++) {
		request = malloc(strlen("SELECT Value FROM AMPLIFICATOR WHERE NameAttack=\"\" AND NameDefense=\"\"") + strlen(selected.type) + strlen((*adv).type[i]) + 1);

		sprintf(request, "SELECT Value FROM AMPLIFICATOR WHERE NameAttack=\"%s\" AND NameDefense=\"%s\"", selected.type, (*adv).type[i]);

		if (mysql_query(mysql, request)){
				free(request);
				MySQL_PrintError("Error query", *mysql);
				return 1;
		}
		free(request);

		result = mysql_store_result(mysql);
		if (result == NULL) {
			MySQL_PrintError("Error extract résult", *mysql);
			return 1;
		}

		row = mysql_fetch_row(result);
		if (row == NULL)
			continue;

		if (!strcmp("0.5", row[0])){
			power /= 2;
		} else if (!strcmp("2", row[0])) {
			power *= 2;
		}
	}

	(*adv).pvActuel -= power;
	if ((*adv).pvActuel < 0)
		(*adv).pvActuel = 0;

	return 0;
}

// display attacks
int displayChoseAttack (SDL_Rect * rectangleChoseAttack, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur, SDL_Rect rectangleAttack[4], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, Pokemon * pokemonPlayer, SDL_Renderer ** renderer) {

	char * request;

	if (loadBMP("../img/attack.bmp", surfaceChoseAttack))
		return 1;

	if (displayAll(textureChoseAttack, surfaceChoseAttack, rectangleChoseAttack, renderer, 400, 500, 800, 400))
		return 1;

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	for (int i = 0; i < 4; i++) {
		request = malloc(strlen((*pokemonPlayer).comp[i].name) + 1);
		strcpy(request, (*pokemonPlayer).comp[i].name);

		*text = TTF_RenderText_Blended(*font, request, black);
		free(request);

		if (displayAll(&(*pokemonPlayer).comp[i].text, text, &(rectangleAttack[i]), renderer, 700, 575 + i * 65, 300, -1))
			return 1;

	}

	return 0;
}

// refresh list of attack
int updateDisplayAtack (SDL_Rect * rectangleChoseAttack, SDL_Rect * rectangleCurseur, SDL_Rect rectangleAttack[4], SDL_Texture ** textureCurseur, SDL_Texture ** textureChoseAttack, Pokemon * pokemonPlayer, SDL_Renderer ** renderer) {

	if (updateRenderer(textureChoseAttack, renderer, rectangleChoseAttack))
		return 1;

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	for (int i = 0; i < 4; i++) {
		if (updateRenderer(&(*pokemonPlayer).comp[i].text, renderer, &(rectangleAttack[i])))
			return 1;
	}

	return 0;
}

// refresh possibles action in fight menu
int updateDisplayChoseActionFight (SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, char poss, SDL_Renderer ** renderer) {

	if (updateRenderer(textureChoseActionFight, renderer, rectangleChoseActionFight))
		return 1;

	switch (poss) {
		case 0:
			(*rectangleCurseur).x = 475;
			(*rectangleCurseur).y = 640;
			break;

		case 1:
			(*rectangleCurseur).x = 875;
			(*rectangleCurseur).y = 640;
			break;

		case 2:
			(*rectangleCurseur).x = 475;
			(*rectangleCurseur).y = 775;
			break;

		case 3:
			(*rectangleCurseur).x = 875;
			(*rectangleCurseur).y = 775;
			break;

		default:
			break;
	}

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	return 0;
}

// displays possibles action in fight
int displayChoseActionFight (SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer) {

	if (loadBMP("../img/choseActionFight.bmp", surfaceChoseActionFight))
		return 1;

	if (displayAll(textureChoseActionFight, surfaceChoseActionFight, rectangleChoseActionFight, renderer, 400, 500, 800, 400))
		return 1;

	if (loadBMP("../img/curseur.bmp", surfaceCurseur))
		return 1;

	if (displayAll(textureCurseur, surfaceCurseur, rectangleCurseur, renderer, 475, 640, 50, 50))
		return 1;

	return 0;
}

// display lvl and pv of a pokmeon
int displayPvPokemon (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Color black, Pokemon pokemonActu, int x, int y, SDL_Renderer ** renderer, SDL_Rect * rectangle) {

	char * request;
	SDL_Rect rectangleText;

	request = malloc(strlen(pokemonActu.name) + sizeof(int) * 3 + strlen(" LVL :  | PV : /") + 1);

	sprintf(request, "%s LVL : %d | PV : %d/%d", pokemonActu.name, pokemonActu.lvl, pokemonActu.pvActuel, pokemonActu.pv);
	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, rectangle, renderer, x, y, 400, -1))
		return 1;

	return 0;
}

// display ia pokemon
int loadDiplayPokemonPlayer (MYSQL * mysql, SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, Pokemon * pokemonActu) {

  char * request;
  int img;
  int i;
  double mul;

  request = malloc(strlen("../img/pokemon/.bmp") + strlen((*pokemonActu).name) + 1);

  strcpy(request, "../img/pokemon/");
  strcat(request, (*pokemonActu).name);
  strcat(request, ".bmp");

  // load home page
  img = loadBMP(request, surface);
  free(request);
  if (img)
    return 1;

  // create texture
  if (createTexture(&((*pokemonActu).img), renderer, surface))
    return 1;

  // load texture
  if (loadTexture(&((*pokemonActu).img), rectangle))
    return 1;

  (*rectangle).x = 200;
  (*rectangle).y = 200;

  if ((*rectangle).w > (*rectangle).h) {
    mul = 200.0/(*rectangle).w;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  } else {
    mul = 200.0/(*rectangle).h;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  }

  // display texture
  if (updateRenderer(&((*pokemonActu).img), renderer, rectangle))
    return 1;

  return 0;
}

// display user pokemon
int loadDiplayPokemonAdv (SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, MYSQL_ROW row) {

  char * request;
  int img;
  double mul;

  request = malloc(strlen("../img/pokemon/.bmp") + strlen(row[0]) + 1);

  strcpy(request, "../img/pokemon/");
  strcat(request, row[0]);
  strcat(request, ".bmp");

  // load home page
  img = loadBMP(request, surface);
  free(request);
  if (img)
    return 1;

  // create texture
  if (createTexture(texture, renderer, surface))
    return 1;

  // load texture
  if (loadTexture(texture, rectangle))
    return 1;

  (*rectangle).x = 1200;
  (*rectangle).y = 200;

  if ((*rectangle).w > (*rectangle).h) {
    mul = 200.0/(*rectangle).w;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  } else {
    mul = 200.0/(*rectangle).h;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  }

  // display texture
  if (updateRenderer(texture, renderer, rectangle))
    return 1;

  return 0;
}

// select user pokemon
int takePokemonUser (MYSQL * mysql, Pokemon * tab) {

	int numRow;
	MYSQL_ROW row;
	MYSQL_RES *result;
	MYSQL_ROW rowPokemon;
	MYSQL_RES *resultPokemon;
	char * request;
	int i;
	int j;

	if (mysql_query(mysql, "SELECT NamePokemon, ID, lvl, XP FROM POKEBALL WHERE IDTrainer=1 AND PC=0 ORDER BY LVL DESC")){
	    MySQL_PrintError("Error query", *mysql);
	    return 1;
	}

	result = mysql_store_result(mysql);
  if (result == NULL) {
    MySQL_PrintError("Error extract résult", *mysql);
		return 1;
  }

	for (i = 0; i < 6; i++){

		row = mysql_fetch_row(result);
		if (row == NULL) {
			strcpy(tab[i].name, "");
			continue;
		}
		strcpy(tab[i].name, row[0]);
		strcpy(tab[i].id, row[1]);
		tab[i].lvl = atoi(row[2]);
		tab[i].xp = atoi(row[3]);

		request = malloc(strlen("SELECT PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"\"") + strlen(tab[i].name) + 1);
		sprintf(request, "SELECT PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"%s\"", tab[i].name);

		if (mysql_query(mysql, request)){
			free(request);
	    MySQL_PrintError("Error query", *mysql);
	    return 1;
		}
		free(request);

		resultPokemon = mysql_store_result(mysql);
	  if (resultPokemon == NULL) {
	    MySQL_PrintError("Error extract résult", *mysql);
			return 1;
	  }

		row = mysql_fetch_row(resultPokemon);
		if (row == NULL)
			return 1;

		tab[i].pv = atoi(row[0]) * tab[i].lvl;
		tab[i].pvActuel = tab[i].pv;
		tab[i].attack = atoi(row[1]) * tab[i].lvl;
		tab[i].defense = atoi(row[2]) * tab[i].lvl;
		tab[i].speed = atoi(row[3]) * tab[i].lvl;

		if (takeComp(mysql, &(tab[i])))
			return 1;

		if (takeTypes(mysql, &(tab[i])))
			return 1;
	}

	return 0;
}

// select ia pokemon
int takePokemonAdv (MYSQL * mysql, Pokemon * adv, int lvlPlayer, MYSQL_ROW row) {

	int numRow;
	char * request;
	MYSQL_RES *result;
	int numRand;

  srand(time(NULL));
  (*adv).lvl = rand()%lvlPlayer + 1;

	request = malloc(strlen("SELECT Name, PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"\"") + strlen(row[0]) + 1);
	strcpy(request, "SELECT Name, PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"");
	strcat(request, row[0]);
	strcat(request, "\"");

	if (mysql_query(mysql, request)){
		free(request);
    MySQL_PrintError("Error query", *mysql);
    return 1;
	}
	free(request);

	result = mysql_store_result(mysql);
  if (result == NULL) {
    MySQL_PrintError("Error extract résult", *mysql);
		return 1;
  }

	row = mysql_fetch_row(result);
	if (row == NULL)
		return 1;

	strcpy((*adv).name, row[0]);
	(*adv).pv = atoi(row[1]) * (*adv).lvl;
	(*adv).pvActuel = atoi(row[1]) * (*adv).lvl;
	(*adv).attack = atoi(row[2]) * (*adv).lvl;
	(*adv).defense = atoi(row[3]) * (*adv).lvl;
	(*adv).speed = atoi(row[4]) * (*adv).lvl;

	if (takeComp(mysql, adv))
		return 1;

	if (takeTypes(mysql, adv))
		return 1;

	return 0;
}

// select and store types of a pokemon
int takeTypes (MYSQL * mysql, Pokemon * pokemon) {

	MYSQL_ROW rowType;
	MYSQL_RES *resultType;
	char * requestType;

	requestType = malloc(strlen("SELECT NameType FROM BELONGSTO WHERE NamePokemon=\"\"") + strlen((*pokemon).name) + 1);
	sprintf(requestType, "SELECT NameType FROM BELONGSTO WHERE NamePokemon=\"%s\"", (*pokemon).name);

	if (mysql_query(mysql, requestType)){
			free(requestType);
			MySQL_PrintError("Error query", *mysql);
			return 1;
	}
	free(requestType);

	resultType = mysql_store_result(mysql);
	if (resultType == NULL) {
		MySQL_PrintError("Error extract résult", *mysql);
		return 1;
	}

	for (int j = 0; j < 2; j++) {
		rowType = mysql_fetch_row(resultType);
		if (rowType == NULL) {
			(*pokemon).type[j][0] = 0;
			continue;
		}
		strcpy((*pokemon).type[j], rowType[0]);
	}

	return 0;
}

// select and store the skills of a pokemon
int takeComp (MYSQL * mysql, Pokemon * pokemon) {

	MYSQL_ROW rowLearn;
	MYSQL_RES *resultLearn;
	char * requestLearn;
	MYSQL_ROW rowAttack;
	MYSQL_RES *resultAttack;
	char * requestAttack;

	requestLearn = malloc(sizeof("SELECT * FROM LEARN WHERE NamePokemon=\"\"") + sizeof((*pokemon).name) + 1);

	sprintf(requestLearn, "SELECT * FROM LEARN WHERE NamePokemon=\"%s\"", (*pokemon).name);

	if (mysql_query(mysql, requestLearn)){
			free(requestLearn);
			MySQL_PrintError("Error query", *mysql);
			return 1;
	}
	free(requestLearn);

	resultLearn = mysql_store_result(mysql);
	if (resultLearn == NULL) {
		MySQL_PrintError("Error extract résult", *mysql);
		return 1;
	}

	for (int j = 0; j < 4; j++) {
		rowLearn = mysql_fetch_row(resultLearn);
		if (rowLearn == NULL)
			return 0;

		requestAttack = malloc(strlen("SELECT * FROM ATTACK WHERE Name=\"\"") + strlen(rowLearn[1]) + 1);
		sprintf(requestAttack, "SELECT * FROM ATTACK WHERE Name=\"%s\"", rowLearn[1]);

		if (mysql_query(mysql, requestAttack)){
				free(requestAttack);
				MySQL_PrintError("Error query", *mysql);
				return 1;
		}
		free(requestAttack);

		resultAttack = mysql_store_result(mysql);
		if (resultAttack == NULL) {
			MySQL_PrintError("Error extract résult", *mysql);
			return 1;
		}
		rowAttack = mysql_fetch_row(resultAttack);

		if (rowAttack == NULL)
			continue;

		strcpy((*pokemon).comp[j].name, rowLearn[1]);
		strcpy((*pokemon).comp[j].type, rowAttack[3]);
		(*pokemon).comp[j].lvl = atoi(rowLearn[2]);
		(*pokemon).comp[j].Power = atoi(rowAttack[1]);
		(*pokemon).comp[j].Acc = atoi(rowAttack[2]);
	}

	return 0;
}

// manage error in homeDisplay
int managefight (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, MYSQL_ROW row) {

  SDL_Surface * surfaceBackground = NULL;
  SDL_Surface * surfacePokemonPlayer = NULL;
  SDL_Surface * surfacePokemonAdv = NULL;
  SDL_Texture * textureBackground = NULL;
  SDL_Texture * texturePokemonPlayer = NULL;
  SDL_Texture * texturePokemonAdv = NULL;
  SDL_Surface * text = NULL;
  SDL_Texture * textureText = NULL;
  SDL_Surface * surfaceChoseActionFight = NULL;
  SDL_Texture * textureChoseActionFight = NULL;
  SDL_Surface * surfaceCurseur = NULL;
  SDL_Texture * textureCurseur = NULL;
  SDL_Surface * surfaceSelect = NULL;
  SDL_Texture * textureSelect = NULL;
  SDL_Surface * surfaceChoseAttack = NULL;
  SDL_Texture * textureChoseAttack = NULL;
	Pokemon tab[6];

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++){
				tab[i].comp[j].text = NULL;
		}
		tab[i].img = NULL;
	}

  int fight = fightDisplay(config, tab, &surfaceChoseAttack, &textureChoseAttack, &surfaceSelect, &textureSelect, &surfaceChoseActionFight, &textureChoseActionFight, &surfaceCurseur, &textureCurseur, &text, &textureText, font, mysql, row, renderer, &surfaceBackground, &textureBackground, &surfacePokemonPlayer, &texturePokemonPlayer, &surfacePokemonAdv, &texturePokemonAdv);
  closeFightDisplay(tab, &surfaceChoseAttack, &textureChoseAttack, &surfaceSelect, &textureSelect, &surfaceChoseActionFight, &textureChoseActionFight, &surfaceCurseur, &textureCurseur, &text, &textureText, &surfaceBackground, &textureBackground, &surfacePokemonPlayer, &texturePokemonPlayer, &surfacePokemonAdv, &texturePokemonAdv);

  return fight;
}

// free surface and texture used in menu
void closeFightDisplay (Pokemon tab[6], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv) {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++){
			if (tab[i].comp[j].text != NULL){
				SDL_DestroyTexture(tab[i].comp[j].text);
			}
		}
		if (tab[i].img != NULL){
			SDL_DestroyTexture(tab[i].img);
		}
	}

	if (*surfaceChoseAttack != NULL)
    SDL_FreeSurface(*surfaceChoseAttack);
  if (*textureChoseAttack != NULL)
    SDL_DestroyTexture(*textureChoseAttack);

	if (*surfaceSelect != NULL)
    SDL_FreeSurface(*surfaceSelect);
  if (*textureSelect != NULL)
    SDL_DestroyTexture(*textureSelect);

	if (*surfaceChoseActionFight != NULL)
    SDL_FreeSurface(*surfaceChoseActionFight);
  if (*textureChoseActionFight != NULL)
    SDL_DestroyTexture(*textureChoseActionFight);

	if (*surfaceCurseur != NULL)
		SDL_FreeSurface(*surfaceCurseur);
	if (*textureCurseur != NULL)
		SDL_DestroyTexture(*textureCurseur);

  if (*text != NULL)
    SDL_FreeSurface(*text);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);

  if (*surfaceBackground != NULL)
    SDL_FreeSurface(*surfaceBackground);
  if (*textureBackground != NULL)
    SDL_DestroyTexture(*textureBackground);

  if (*surfacePokemonPlayer != NULL)
    SDL_FreeSurface(*surfacePokemonPlayer);
  if (*texturePokemonPlayer != NULL)
    SDL_DestroyTexture(*texturePokemonPlayer);

  if (*surfacePokemonAdv != NULL)
    SDL_FreeSurface(*surfacePokemonAdv);
  if (*texturePokemonAdv != NULL)
    SDL_DestroyTexture(*texturePokemonAdv);
}

/********************************************
*****************CHOSE POKEMON***************
********************************************/

int switchDisplay (Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer) {

	SDL_Rect rectangleCurseur;
	SDL_Rect rectangleSwitch;
	SDL_Rect rectangle[6];

	if (loadBMP("../img/chosePokemon.bmp", surfaceSwitch))
    return 1;

  if (displayAll(textureSwitch, surfaceSwitch, &rectangleSwitch, renderer, 0, 0, 1600, 900))
    return 1;

	if (displaySixPokemon (text, textureText, font, player, rectangle, surfacePokemon, renderer))
		return 1;

  if (loadBMP("../img/curseur.bmp", surfaceCurseur))
    return 1;

  if (displayAll(textureCurseur, surfaceCurseur, &rectangleCurseur, renderer, 10, 110, 25, 25))
    return 1;

	return manageSwitchPokemonDisplay (config, text, textureText, font, &rectangleCurseur, &rectangleSwitch, rectangle, player, surfacePokemon, surfaceCurseur, textureCurseur, surfaceSwitch, textureSwitch, renderer);
}

int manageSwitchPokemonDisplay (Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer) {

	SDL_bool programLaunched = SDL_TRUE;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						(*rectangleCurseur).y -= ((*rectangleCurseur).y == 110) ? - 80 * 5 : 80;

					} else if (event.key.keysym.sym == config.down) {

						(*rectangleCurseur).y += ((*rectangleCurseur).y == 110 + 80 * 5) ? - 80 * 5 : 80;

					} else if (event.key.keysym.sym == config.validate) {

						return (((*rectangleCurseur).y - 110) / 80) + 10;

					}
          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }
			if (updatePokeball (text, textureText, font, rectangleCurseur, rectangleSwitch, rectangle, player, surfacePokemon, surfaceCurseur, textureCurseur, surfaceSwitch, textureSwitch, renderer))
				return 1;
    }
  }

  return 0;
}

int updatePokeball (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer) {

	if (updateRenderer(textureSwitch, renderer, rectangleSwitch))
		return 1;

	if (displaySixPokemon (text, textureText, font, player, rectangle, surfacePokemon, renderer))
		return 1;

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	return 0;
}

int displaySixPokemon (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Rect rectangle[6], SDL_Surface ** surfacePokemon, SDL_Renderer ** renderer) {

	char * request;
	SDL_Rect rectanglePV;
	SDL_Color black = {0, 0, 0};

	for (int i = 0; i < 6; i++) {

		if (strcmp(player[i].name, "")) {
			if (player[i].img == NULL) {

				request = malloc(strlen("../img/pokemon/.bmp") + strlen(player[i].name) + 1);
				sprintf(request, "../img/pokemon/%s.bmp", player[i].name);

				if (loadBMP(request, surfacePokemon)){
					free(request);
					return 1;
				}
				free(request);

			  if (displayAll(&(player[i].img), surfacePokemon, &(rectangle[i]), renderer, 50, 100 + 80 * i, 50, 50))
			    return 1;

			} else {
				rectangle[i].x = 50;
				rectangle[i].y = 100 + 80 * i;
				rectangle[i].w = 50;
				rectangle[i].h = 50;

				if (updateRenderer(&(player[i].img), renderer, &(rectangle[i])))
					return 1;
			}
		}

		if (displayPvPokemon (text, textureText, font, black, player[i], 200, 100 + 80 * i, renderer, &rectanglePV))
			return 1;
	}

	return 0;
}

int manageSwitchPokemon (Config config, TTF_Font ** font, Pokemon player[6], SDL_Renderer ** renderer) {

  SDL_Surface * surfaceCurseur = NULL;
  SDL_Texture * textureCurseur = NULL;
  SDL_Surface * surfaceSwitch = NULL;
  SDL_Texture * textureSwitch = NULL;
  SDL_Surface * surfacePokemon = NULL;
	SDL_Surface * text = NULL;
	SDL_Texture * textureText = NULL;
  //SDL_Surface * surfaceValidate = NULL;
  //SDL_Texture * textureValidate = NULL;
	int retour = switchDisplay(config, &text, &textureText, font, player, &surfacePokemon, &surfaceCurseur, &textureCurseur, &surfaceSwitch, &textureSwitch, renderer);
	closeSwitchPokemon(&text, &textureText, &surfacePokemon, &surfaceCurseur, &textureCurseur, &surfaceSwitch, &textureSwitch);

	return retour;
}

void closeSwitchPokemon (SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch) {

	if (*surfaceCurseur != NULL)
    SDL_FreeSurface(*surfaceCurseur);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);
	if (*surfaceSwitch != NULL)
    SDL_FreeSurface(*surfaceSwitch);
  if (*textureSwitch != NULL)
    SDL_DestroyTexture(*textureSwitch);
	if (*surfacePokemon != NULL)
    SDL_FreeSurface(*surfacePokemon);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);
	if (*text != NULL)
    SDL_FreeSurface(*text);

}

/********************************************
*********************MENU********************
********************************************/

// Configuration Menu
int menuDisplay(SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur){

  SDL_Rect rectangleMenu;
  SDL_Rect rectangleCurseur;

  if (loadDiplayMenu (surfaceMenu, textureMenu, renderer, &rectangleMenu))
    return 1;

  if (loadBMP("../img/curseur.bmp", surfaceCurseur))
    return 1;

  if (displayAll(textureCurseur, surfaceCurseur, &rectangleCurseur, renderer, 685, 355, 25, 25))
    return 1;

  if (manageEventMenu (texture, texturePlayer, renderer, rectangle, &rectangleMenu, &rectangleCurseur, rectanglePlayer, textureMenu, textureCurseur))
    return 1;

  return 0;
}

// load and display menu
int loadDiplayMenu (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Renderer ** renderer, SDL_Rect * rectangleMenu) {

  // load home page
  if (loadBMP("../img/menu.bmp", surfaceMenu))
    return 1;

  // create texture
  if (createTexture(textureMenu, renderer, surfaceMenu))
    return 1;

  // load texture
  if (loadTexture(textureMenu, rectangleMenu))
    return 1;

  (*rectangleMenu).w = 250;
  (*rectangleMenu).h = 500;
  (*rectangleMenu).x = (1600-(*rectangleMenu).w)/2;
  (*rectangleMenu).y = (900-(*rectangleMenu).h)/2;

  // display texture
  if (updateRenderer(textureMenu, renderer, rectangleMenu))
    return 1;

  return 0;
}

// manage event for menu display
int manageEventMenu (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Rect * rectanglePlayer, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur) {

  SDL_bool programLaunched = SDL_TRUE;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_UP://Vers le haut
              if((*rectangleCurseur).y >= 355){
                (*rectangleCurseur).y -= 75;
                if (updateMenuDisplay(texture, texturePlayer, renderer, rectangle, rectanglePlayer, rectangleMenu, rectangleCurseur, textureMenu, textureCurseur))
                  return 1;
              }
              break;

            case SDLK_DOWN://Vers le bas
              if((*rectangleCurseur).y <= 530){
                (*rectangleCurseur).y += 75;
                if (updateMenuDisplay(texture, texturePlayer, renderer, rectangle, rectanglePlayer, rectangleMenu, rectangleCurseur, textureMenu, textureCurseur))
                  return 1;
              }
              break;

            default:
              break;
          }
          break;

        case SDL_KEYUP:
          switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
              programLaunched = SDL_FALSE; //fermer la map
              break;

            default:
              break;
          }
          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }
    }
  }

  return 0;
}

// refresh menu
int updateMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(texture, renderer, rectangle))
    return 1;
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;
  if (updateRenderer(textureMenu, renderer, rectangleMenu))
    return 1;
  if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
    return 1;

  return 0;
}

// manage error in homeDisplay
int manageMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer) {

  SDL_Surface * surfaceMenu = NULL;
  SDL_Texture * textureMenu = NULL;
  SDL_Surface * surfaceCurseur = NULL;
  SDL_Texture * textureCurseur = NULL;

  int menu = menuDisplay(texture, texturePlayer, renderer, rectangle, rectanglePlayer, &surfaceMenu, &textureMenu, &surfaceCurseur, &textureCurseur);
  closeMenuDisplay(&surfaceMenu, &textureMenu, &surfaceCurseur, &textureCurseur);

  if (menu)
    return 1;

  return 0;
}

// fre surface and texture used in menu
void closeMenuDisplay (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur) {
  if (*surfaceMenu != NULL)
    SDL_FreeSurface(*surfaceMenu);
  if (*textureMenu != NULL)
    SDL_DestroyTexture(*textureMenu);
  if (*surfaceCurseur != NULL)
    SDL_FreeSurface(*surfaceCurseur);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);
}

/********************************************
*********************HOME********************
********************************************/

int MatriceHome(int x, int y){
int matriceHomeInt[12][25]={
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,1},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,0,1},
{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
{0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1},
{1,1,1,0,0,0,1,0,0,0,0,0,1,1,0,0,0,1,0,0},
{1,1,1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0},
{1,0,0,1,1,2,1,2,1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0},
{0,0,0,1,1,0,0,1,1,3,1,1,0,0,1,1,1,1,1,0}
};
return matriceHomeInt[y/60][(x-200)/60];
}

//Display home
int homeDisplay(SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc){

  SDL_Rect rectangleHome;
  SDL_Rect rectanglePlayer;
  SDL_Rect rectanglePc;

  SDL_RenderClear(*renderer);

  // HOME
  // load and display home
  if (loadDiplayHome(renderer, surfaceHome, textureHome, &rectangleHome))

    return 1;

  //PERSONNAGE
  // load and display player in home
  if (displayPlayerHome(renderer, texturePlayer, &rectanglePlayer))
    return 1;

  if (manageEventHomeGame(renderer,surfaceHome,textureHome,&rectangleHome,texturePlayer,&rectanglePlayer,texturePc, &rectanglePc))
    return 1;

  return 0;
}

int displayPlayerHome (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer) {

  // load texture
  if (loadTexture(texturePlayer, rectanglePlayer))
    return 1;
(*rectanglePlayer).w = 60;
(*rectanglePlayer).h = 60;
(*rectanglePlayer).x = 200+60*9;
(*rectanglePlayer).y = 60*11;

  // display texture
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;

  return 0;
}

// load and dipslay home image
int loadDiplayHome (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

  // load home page
  if (loadBMP("../img/home.bmp", surfaceHome))
    return 1;

  // create texture
  if (createTexture(textureHome, renderer, surfaceHome))
    return 1;

  // load texture
  if (loadTexture(textureHome, rectangleHome))
    return 1;

  (*rectangleHome).w = 1200;
  (*rectangleHome).h = 900;
  (*rectangleHome).x = (1600-(*rectangleHome).w)/2;
  (*rectangleHome).y = (900-(*rectangleHome).h)/2;

  // display texture
  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;

  return 0;
}

int manageEventHomeGame (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** texturePc, SDL_Rect * rectanglePc) {

  SDL_bool programLaunched = SDL_TRUE;
  int nextCase;

  // event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
              programLaunched = SDL_FALSE; //Close Home
              break;

            case SDLK_UP://Vers le haut
              nextCase = MatriceHome((*rectanglePlayer).x, (*rectanglePlayer).y-60);
              if (nextCase == 1){
                (*rectanglePlayer).y -= 60;
                if (updateMainHomeDisplay (renderer, textureHome, rectangleHome, texturePlayer, rectanglePlayer))
                  return 1;
              }else if(nextCase==2){
                    managePcDisplay(renderer);
              }else if(nextCase==3){
                   return 0;
              }
              break;

            case SDLK_DOWN://Vers le bas
              nextCase = MatriceHome((*rectanglePlayer).x, (*rectanglePlayer).y+60);
              if (nextCase == 1){
                (*rectanglePlayer).y += 60;
                if (updateMainHomeDisplay (renderer, textureHome, rectangleHome, texturePlayer, rectanglePlayer))
                  return 1;
              }else if(nextCase==2){
                    managePcDisplay(renderer);
              }else if(nextCase==3){
                   return 0;
              }
              break;

            case SDLK_RIGHT://Aller à droite
              nextCase = MatriceHome((*rectanglePlayer).x+60, (*rectanglePlayer).y);
              if (nextCase == 1){
                (*rectanglePlayer).x += 60;
                if (updateMainHomeDisplay (renderer, textureHome, rectangleHome, texturePlayer, rectanglePlayer))
                  return 1;
              }else if (nextCase==2){
                        managePcDisplay(renderer);
              }else if(nextCase==3){
                   return 0;
              }
              break;

            case SDLK_LEFT: //Go to the left
              nextCase = MatriceHome((*rectanglePlayer).x-60, (*rectanglePlayer).y);
              if (nextCase == 1){
                (*rectanglePlayer).x -= 60;
                if (updateMainHomeDisplay (renderer, textureHome, rectangleHome, texturePlayer, rectanglePlayer))
                  return 1;
              }else if(nextCase==2){
                    managePcDisplay(renderer);
              }else if(nextCase==3){
                   return 0;
              }
              break;

            case SDLK_SPACE: //open menu
              manageMenuDisplay (textureHome, texturePlayer, renderer, rectangleHome, rectanglePlayer);
              if (updateMainHomeDisplay (renderer, textureHome, rectangleHome, texturePlayer, rectanglePlayer))
                return 1;
              break;

            default:
              break;
          }
          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }

    }
  }
  return 0;
}

//Update Home Display
int updateMainHomeDisplay (SDL_Renderer ** renderer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;

  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;

  return 0;
}

// manage error in homeDisplay
int manageHomeDisplay (Config config, SDL_Renderer ** renderer, SDL_Texture ** texturePlayer) {

  SDL_Surface * surfaceHome = NULL;
  SDL_Texture * textureHome = NULL;
  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  int home = homeDisplay(renderer, texturePlayer, &surfaceHome, &textureHome, &surfacePc, &texturePc);

  closeHomeDisplay(&surfaceHome, &textureHome, &surfacePc, &texturePc);

  return home;
}

// free surface and texture used in homeDisplay
void closeHomeDisplay (SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc) {
  if (*surfaceHome != NULL)
    SDL_FreeSurface(*surfaceHome);
  if (*textureHome != NULL)
    SDL_DestroyTexture(*textureHome);
 if (*surfacePc != NULL)
    SDL_FreeSurface(*surfacePc);
  if (*texturePc != NULL)
    SDL_DestroyTexture(*texturePc);
}


/********************************************
**********************PC*********************
********************************************/

//Configuration Pc
int pcDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseurPc){

  SDL_Rect rectanglePc;
  SDL_Rect rectangleCurseurPc;

  if (loadDiplayPc (surfacePc, texturePc, renderer, &rectanglePc))
    return 1;

  if (loadDiplayCurseurPc (surfaceCurseurPc, textureCurseurPc, renderer, &rectangleCurseurPc))
    return 1;

  if (manageEventPc (renderer, surfacePc, texturePc, &rectanglePc, surfaceCurseurPc, textureCurseurPc, &rectangleCurseurPc))
    return 1;

  return 0;
}

// load and display curseur
int loadDiplayCurseurPc (SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPc) {

  //CURSEUR
  // load curseur
  if (loadBMP("../img/curseur.bmp", surfaceCurseuPc))
    return 1;

  // create curseur
  if (createTexture(textureCurseurPc, renderer, surfaceCurseuPc))
    return 1;

  // load texture
  if (loadTexture(textureCurseurPc, rectangleCurseurPc))
    return 1;

  (*rectangleCurseurPc).w = 25;
  (*rectangleCurseurPc).h = 25;
  (*rectangleCurseurPc).x = 685;
  (*rectangleCurseurPc).y = 355;

  // display texture
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;

  return 0;
}

// load and display pc
int loadDiplayPc (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc) {

  // load home page
  if (loadBMP("../img/pcMenu.bmp", surfacePc))
    return 1;

  // create texture
  if (createTexture(texturePc, renderer, surfacePc))
    return 1;

  // load texture
  if (loadTexture(texturePc, rectanglePc))
    return 1;

  (*rectanglePc).w = 250;
  (*rectanglePc).h = 500;
  (*rectanglePc).x = (1600-(*rectanglePc).w)/2;
  (*rectanglePc).y = (900-(*rectanglePc).h)/2;

  // display texture
  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;

  return 0;
}


int manageEventPc (SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Rect * rectangleCurseurPc) {

  SDL_bool programLaunched = SDL_TRUE;
  int nextCase;

  // event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
              programLaunched = SDL_FALSE; //Close the pc
              break;

            case SDLK_UP://Go Up
              nextCase = MatriceHome((*rectangleCurseurPc).x, (*rectangleCurseurPc).y-65);
              if (nextCase == 1){
                (*rectangleCurseurPc).y -= 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
             /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_DOWN://Go Down
              nextCase = MatriceHome((*rectangleCurseurPc).x, (*rectangleCurseurPc).y+65);
              if (nextCase == 1){
                (*rectangleCurseurPc).y += 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
              /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_RIGHT://To the right
              nextCase = MatriceHome((*rectangleCurseurPc).x+65, (*rectangleCurseurPc).y);
              if (nextCase == 1){
                (*rectangleCurseurPc).x += 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
              /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_LEFT: //The left
              nextCase = MatriceHome((*rectangleCurseurPc).x-65, (*rectangleCurseurPc).y);
              if (nextCase == 1){
                (*rectangleCurseurPc).x -= 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
              /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_SPACE: //Ouvrir menu
              manageMenuDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc);
              if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                return 1;
              break;

            default:
              break;
          }
          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }

    }
  }
  return 0;
}

// refresh pc
int updateMainPcDisplay (SDL_Texture ** texturePc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc, SDL_Rect * rectangleCurseurPc) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;

  return 0;
}

// manage error in pcDisplay
int managePcDisplay (SDL_Renderer ** renderer) {

  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  SDL_Surface * surfaceCurseurPc = NULL;
  SDL_Texture * textureCurseurPc = NULL;

  int pc = pcDisplay(renderer, &surfacePc, &texturePc, &surfaceCurseurPc, &textureCurseurPc);
  closePcDisplay(&surfacePc, &texturePc, &surfaceCurseurPc, &textureCurseurPc);

  if (pc)
    return 1;

  return 0;
}

// free surface and texture used in pcDisplay
void closePcDisplay (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseur) {
  if (*surfacePc != NULL)
    SDL_FreeSurface(*surfacePc);
  if (*texturePc != NULL)
    SDL_DestroyTexture(*texturePc);
  if (*surfaceCurseurPc != NULL)
    SDL_FreeSurface(*surfaceCurseurPc);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);
}

/********************************************
******************HOME PAGE******************
********************************************/

int displayHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, SDL_Surface ** surfaceHomePage, SDL_Texture ** textureHomePage, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur) {

	SDL_Rect rectangleHomePage;
	SDL_Rect rectangleCurseur;

	if (loadBMP("../img/homePage.bmp", surfaceHomePage))
		return 1;

	if (displayAll(textureHomePage, surfaceHomePage, &rectangleHomePage, renderer, 0, 0, 1600, 900))
		return 1;

	if (loadBMP("../img/curseur.bmp", surfaceCurseur))
		return 1;

	if (displayAll(textureCurseur, surfaceCurseur, &rectangleCurseur, renderer, 450, 450, 50, 50))
		return 1;

	if (manageEventHomePage(config, font, renderer, mysql, &rectangleHomePage, textureHomePage, &rectangleCurseur, textureCurseur))
		return 1;

	return 0;
}

int manageEventHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, SDL_Rect * rectangleHomePage, SDL_Texture ** textureHomePage, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur) {

	SDL_bool programLaunched = SDL_TRUE;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYUP:
					if (event.key.keysym.sym == (*config).escape) {
						programLaunched = SDL_FALSE;
					} else if (event.key.keysym.sym == (*config).up) {
						(*rectangleCurseur).y -= ((*rectangleCurseur).y == 450) ? - 150 : 150;
					} else if (event.key.keysym.sym == (*config).down) {
						(*rectangleCurseur).y += ((*rectangleCurseur).y == 450) ? 150 : - 150;
					} else if (event.key.keysym.sym == (*config).down) {
						(*rectangleCurseur).y += ((*rectangleCurseur).y == 450) ? 150 : - 150;
					} else if (event.key.keysym.sym == (*config).validate) {
						if ((*rectangleCurseur).y == 450){
							if (manageMainGame (*config, font, renderer, mysql))
								return 1;
						} else {
							if (manageDefineKey(config, renderer))
								return 1;
						}
					}
					if (updateHomePage(renderer, rectangleHomePage, textureHomePage, rectangleCurseur, textureCurseur))
						return 1;
          break;

        case SDL_QUIT:
          programLaunched = SDL_FALSE;
          break;

        default:
          break;
      }
    }
  }

  return 0;
}

int updateHomePage (SDL_Renderer ** renderer, SDL_Rect * rectangleHomePage, SDL_Texture ** textureHomePage, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur) {

	SDL_RenderClear(*renderer);

	if (updateRenderer(textureHomePage, renderer, rectangleHomePage))
		return 1;
	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	return 0;
}

int manageHomePage (Config * config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql) {

	SDL_Surface * surfaceHomePage = NULL;
  SDL_Texture * textureHomePage = NULL;
	SDL_Surface * surfaceCurseur = NULL;
  SDL_Texture * textureCurseur = NULL;

	int homePage = displayHomePage(config, font, renderer, mysql, &surfaceHomePage, &textureHomePage, &surfaceCurseur, &textureCurseur);
	closeHomePage(&surfaceHomePage, &textureHomePage, &surfaceCurseur, &textureCurseur);

	return 0;
}

void closeHomePage (SDL_Surface ** surfaceHomePage, SDL_Texture ** textureHomePage, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur) {

	if (*surfaceHomePage != NULL)
    SDL_FreeSurface(*surfaceHomePage);
  if (*textureHomePage != NULL)
    SDL_DestroyTexture(*textureHomePage);
	if (*surfaceCurseur != NULL)
    SDL_FreeSurface(*surfaceCurseur);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);

}

/********************************************
********************CONFIG*******************
********************************************/

// configure player keys
int configKey (Config * config, SDL_Renderer ** renderer) {

	FILE * fileConfig;
	int key;
	char nameKey[50];
	int count = 0;

	fileConfig = fopen("config.dat", "rb");

	fscanf(fileConfig, "%s\n", nameKey);

	while (count < 8) {

		fseek(fileConfig, 0, SEEK_SET);
		count = 0;

		while (!feof(fileConfig) && strcmp(nameKey, "KEY:")) {
			fscanf(fileConfig, "%s:\n", nameKey);
		}

		if (feof(fileConfig)) {
			if (manageDefineKey(config, renderer))
				return 1;
			fseek(fileConfig, 0, SEEK_SET);
		}

		while (!feof(fileConfig) && count < 8) {

			fscanf(fileConfig, "%s : %d\n", nameKey, &key);

			if (strcmp(nameKey, "escape") == 0) {
				(*config).escape = key;
				count++;
			} else if (strcmp(nameKey,"validate") == 0) {
				(*config).validate = key;
				count++;
			} else if (strcmp(nameKey, "cancel") == 0) {
				(*config).cancel = key;
				count++;
			} else if (strcmp(nameKey, "up") == 0) {
				(*config).up = key;
				count++;
			} else if (strcmp(nameKey, "down") == 0) {
				(*config).down = key;
				count++;
			} else if (strcmp(nameKey, "right") == 0) {
				(*config).right = key;
				count++;
			} else if (strcmp(nameKey, "left") == 0) {
				(*config).left = key;
				count++;
			} else if (strcmp(nameKey, "inventory") == 0) {
				(*config).inventory = key;
				count++;
			}
		}

		if (count < 8) {
			if (manageDefineKey(config, renderer))
				return 1;
		}
	}

	fclose(fileConfig);
	return 0;
}

int defineKey (Config * config, SDL_Texture ** texture, SDL_Surface ** page, SDL_Renderer ** renderer) {

	FILE * fileConfig;
	SDL_Rect rectangle;
	int key;
	char nameAction[8][20] = {"escape", "validate", "cancel", "up", "down", "right", "left", "inventory"};
	char nameFile[8][30] = {"../img/quitter.bmp", "../img/valider.bmp", "../img/annuler.bmp", "../img/haut.bmp", "../img/bas.bmp", "../img/droite.bmp", "../img/gauche.bmp", "../img/inventaire.bmp"};

	fileConfig = fopen("config.dat", "r+b");

	fprintf(fileConfig, "KEY:\n");

	for (int i = 0; i < 8; i++) {

		if (loadBMP(nameFile[i], page))
			return 1;

		if (displayAll(texture, page, &rectangle, renderer, 0, 0, -1, -1))
			return 1;

		key = pressedKey();
		fprintf(fileConfig, "%s : %d\n", nameAction[i], key);
	}

	fclose(fileConfig);
	configKey(config, renderer);
	return 0;
}

int pressedKey () {

	while (1) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_KEYUP:
					return event.key.keysym.sym;

				case SDL_QUIT:
					return 0;

				default:
					break;
			}
		}
	}
}

int manageDefineKey (Config * config, SDL_Renderer ** renderer) {

	SDL_Texture * texture = NULL;
	SDL_Surface * page = NULL;

	int define = defineKey(config, &texture, &page, renderer);
	closeDefineKey (&texture, &page);

	return define;
}

void closeDefineKey (SDL_Texture ** texture, SDL_Surface ** page) {

	if (*page != NULL)
    SDL_FreeSurface(*page);
  if (*texture != NULL)
    SDL_DestroyTexture(*texture);
}

/********************************************
*****************MANAGE ERROR****************
********************************************/

int displayAll (SDL_Texture ** texture, SDL_Surface ** surface, SDL_Rect * rectangle, SDL_Renderer ** renderer, int x, int y, int w, int h) {

	// create texture
	if (createTexture(texture, renderer, surface))
		return 1;

	// load texture
	if (loadTexture(texture, rectangle))
		return 1;

	(*rectangle).x = x;
	(*rectangle).y = y;
	if (w != -1)
		(*rectangle).w = w;
	if (h != -1)
		(*rectangle).h = h;

	// display texture
	if (updateRenderer(texture, renderer, rectangle))
		return 1;

	return 0;
}

// create window
int createWindow (SDL_Window ** window, int x, int y) {

  *window = SDL_CreateWindow("pokemon 20/20", 0, 0, x, y, SDL_WINDOW_FULLSCREEN);
  if (*window == NULL) {
    SDL_PrintError("Error create window");
    return 1;
  }

  return 0;
}

// create texture
int createTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Surface ** surface) {

  *texture = SDL_CreateTextureFromSurface(*renderer, *surface);
  if (*texture == NULL) {
    SDL_PrintError("Error create texture");
    return 1;
  }

  return 0;
}

// load texture
int loadTexture (SDL_Texture ** texture, SDL_Rect * rectangle) {

  // load texture
  if(SDL_QueryTexture(*texture, NULL, NULL, &(*rectangle).w, &(*rectangle).h) != 0){
    SDL_PrintError("Error loading texture");
    return 1;
  }

  return 0;
}

// create renderer
int createRenderer (SDL_Renderer ** renderer, SDL_Window ** window) {

  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
  if (*renderer == NULL) {
    SDL_PrintError("Error create renderer");
    return 1;
  }

  return 0;
}

// reload renderer
int updateRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle) {

  // copy texture
  if(SDL_RenderCopy(*renderer, *texture, NULL, rectangle)){
    SDL_PrintError("Error display texture");
  return 1;
  }

  // update renderer
  SDL_RenderPresent(*renderer);

  return 0;
}

int loadFont (TTF_Font ** font) {

  *font = TTF_OpenFont("SourceCodePro-Regular.ttf", 50);
  if (*font == NULL) {
    TTF_PrintError("Error load TTF font");
    return 1;
  }

  return 0;
}

// start SDL
int initSDL () {

  // init SDL
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    SDL_PrintError("Error init SDL");
    return 1;
  }

  if (TTF_Init() == -1){
    TTF_PrintError("Error init TTF");
    return 1;
  }

  return 0;
}

// init MySQL and connect database
int connectDataBase (MYSQL * mysql) {

  // init MySQL
  if (!mysql_init(mysql)) {
    MySQL_PrintError("Error init MySQL", *mysql);
    return 1;
  }

  // connect database
  if (!mysql_real_connect(mysql, "localhost", "user", "azerty", "pokemon", 80, NULL, 0)) {
    MySQL_PrintError("Error connect database", *mysql);
    return 1;
  }
  return 0;
}

// laod BMP
int loadBMP (const char * img, SDL_Surface ** surface) {

  // load img
  *surface = SDL_LoadBMP(img);
  if (*surface == NULL) {
    SDL_PrintError("Error loading image");
    return 1;
  }

  return 0;
}

// display error TTF
void TTF_PrintError(const char * message) {

  printf("%s : %s\n", message, TTF_GetError());
}

// display error SDL
void SDL_PrintError(const char * message) {

  printf("%s : %s\n", message, SDL_GetError());
}

void MySQL_PrintError(const char * message, MYSQL mysql) {

  printf("%s : %d > %s\n", message, mysql_errno(&mysql), mysql_error(&mysql));
}
