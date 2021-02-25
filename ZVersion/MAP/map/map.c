#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <mysql/mysql.h>

/********************************************
*******************TYPE DEF******************
********************************************/

typedef struct Pokemon {

	char name[100];
	int pv[100];
	int pvActuel[100];
	int attack[100];
	int defense[100];
	int speed[100];
	int lvl[100];

} Pokemon;

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
int mainGameDisplay (TTF_Font ** font, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, MYSQL * mysql);
int manageEventMainGame (TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, MYSQL * mysql);
int updateMainGateDisplay (SDL_Renderer ** renderer, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int manageMainGame (TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql);
void closeMainGameDisplay (SDL_Surface ** map, SDL_Texture ** texture, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer);
int randomAggro (TTF_Font ** font, SDL_Renderer ** renderer, int nextCase, MYSQL * mysql);
int randomChoseFight (TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, const char * type);

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
int manageHomeDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer);
int homeDisplay(SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc);
int loadDiplayHome (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int updateMainHomeDisplay (SDL_Renderer ** renderer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int displayPlayerHome (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer);
int manageEventHomeGame (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** texturePc, SDL_Rect * rectanglePc);

//PC
int pcDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseurPc, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion);
int loadDiplayCurseurPc (SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPc);
int loadDiplayPc (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc);
int updateMainPcDisplay (SDL_Texture ** texturePc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc, SDL_Rect * rectangleCurseurPc, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int manageEventPc (SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Rect * rectangleCurseurPc, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion);
int managePcDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome);
void closePcDisplay (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseur);

//Potion
int potionDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePotion, SDL_Texture ** texturePotion, SDL_Surface ** surfaceCurseurPotion, SDL_Texture ** textureCurseurPotion, SDL_Texture ** flayer, SDL_Texture ** textureHome);
int loadDiplayPotion (SDL_Surface ** surfacePotion, SDL_Texture ** texturePotion, SDL_Renderer ** renderer, SDL_Rect * rectanglePotion);
int loadDiplayCurseurPotion (SDL_Surface ** surfaceCurseurPotion, SDL_Texture ** textureCurseurPotion, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPotion);
int updateMainPotionDisplay (SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Renderer ** renderer, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int manageEventPotion (SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Renderer ** renderer, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int managePotionDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome);
void closePotionDisplay (SDL_Surface ** surfacePotion, SDL_Texture ** texturePotion, SDL_Surface ** surfaceCurseurPotion, SDL_Texture ** textureCurseurPotion);

//Reminder
int reminderDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfaceReminder, SDL_Texture ** textureReminder, SDL_Surface ** surfaceCurseurReminder, SDL_Texture ** textureCurseurReminder, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome);
int loadDiplayCurseurReminder (SDL_Surface ** surfaceCurseurReminder, SDL_Texture ** textureCurseurReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurReminder);
int loadDiplayReminder (SDL_Surface ** surfaceReminder, SDL_Texture ** textureReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleReminder);
int updateMainReminderDisplay (SDL_Texture ** textureReminder, SDL_Texture ** textureCurseurReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleReminder, SDL_Rect * rectangleCurseurReminder, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int manageEventReminder (SDL_Texture ** textureReminder, SDL_Texture ** textureCurseurReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleReminder, SDL_Rect * rectangleCurseurReminder, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int manageReminderDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome);
void closeReminderDisplay (SDL_Surface ** surfaceReminder, SDL_Texture ** textureReminder, SDL_Surface ** surfaceCurseurReminder, SDL_Texture ** textureCurseurReminder);

//Pokeballs
int pokeballsDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePokeballs, SDL_Texture ** texturePokeballs, SDL_Surface ** surfaceCurseurPokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome);
int loadDiplayCurseurPokeballs (SDL_Surface ** surfaceCurseurPokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPokeballs);
int loadDiplayPokeballs (SDL_Surface ** surfacePokeballs, SDL_Texture ** texturePokeballs, SDL_Renderer ** renderer, SDL_Rect * rectanglePokeballs);
int updateMainPokeballsDisplay (SDL_Texture ** texturePokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Renderer ** renderer, SDL_Rect * rectanglePokeballs, SDL_Rect * rectangleCurseurPokeballs, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int manageEventPokeballs (SDL_Texture ** texturePokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Renderer ** renderer, SDL_Rect * rectanglePokeballs, SDL_Rect * rectangleCurseurPokeballs, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome);
int managePokeballsDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome);
void closePokeballsDisplay (SDL_Surface ** surfacePokeballs, SDL_Texture ** texturePokeballs, SDL_Surface ** surfaceCurseurPokeballs, SDL_Texture ** textureCurseurPokeballs);

// Fight
int fightDisplay (SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, MYSQL * mysql, MYSQL_ROW row, SDL_Renderer ** renderer, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv);
void closeFightDisplay (SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv);
int managefight (TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, MYSQL_ROW row);
int takePokemonUser (MYSQL * mysql, Pokemon * tab);
int takePokemonAdv (MYSQL * mysql, Pokemon * adv, int * lvlPlaye, MYSQL_ROW row);
int loadDiplayPokemonAdv (SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, MYSQL_ROW row);
int loadDiplayPokemonPlayer (MYSQL * mysql, SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, Pokemon pokemonActu);
int displayPvPokemon (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Color black, Pokemon pokemon, int x, SDL_Renderer ** renderer, SDL_Rect * rectangle);
int displayChoseActionFight (SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer);
int updateDisplayChoseActionFight (SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, char poss, SDL_Renderer ** renderer);
int manageEventChoseActionFight (SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer);

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

  manageMainGame (&font, &renderer, &mysql);

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

int mainGameDisplay (TTF_Font ** font, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, MYSQL * mysql) {

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

  if (manageEventMainGame(font, renderer, map,  texture, &rectangle, surfacePlayer, texturePlayer, &rectanglePlayer, mysql))
    return 1;

  return 0;
}

int manageEventMainGame (TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, MYSQL * mysql) {

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
              programLaunched = SDL_FALSE; //fermer la map
              break;

            case SDLK_UP://Vers le haut
              nextCase = matriceMain((*rectanglePlayer).x, (*rectanglePlayer).y-32);
              if (nextCase!=0 && nextCase!=6){
                (*rectanglePlayer).y -= 32;
                if (updateMainGateDisplay (renderer, texture, rectangle, texturePlayer, rectanglePlayer))
                  return 1;
                if (nextCase > 2) {
                  if (randomAggro(font, renderer, nextCase, mysql))
                    return 1;
                }
              }else if(nextCase==6){
			manageHomeDisplay(renderer, texturePlayer);
              }
              break;

            case SDLK_DOWN://Vers le bas
              nextCase = matriceMain((*rectanglePlayer).x, (*rectanglePlayer).y+32);
              if (nextCase!=0 && nextCase!=6){
                (*rectanglePlayer).y += 32;
                if (updateMainGateDisplay (renderer, texture, rectangle, texturePlayer, rectanglePlayer))
                  return 1;
                if (nextCase > 2) {
                  if (randomAggro(font, renderer, nextCase, mysql))
                    return 1;
                }
              }else if(nextCase==6){
			manageHomeDisplay(renderer, texturePlayer);
              }
              break;

            case SDLK_RIGHT://Aller à droite
              nextCase = matriceMain((*rectanglePlayer).x+32, (*rectanglePlayer).y);
              if (nextCase!=0 && nextCase!=6){
                (*rectanglePlayer).x += 32;
                if (updateMainGateDisplay (renderer, texture, rectangle, texturePlayer, rectanglePlayer))
                  return 1;
                if (nextCase > 2) {
                  if (randomAggro(font, renderer, nextCase, mysql))
                    return 1;
                }
              }else if(nextCase==6){
			manageHomeDisplay(renderer, texturePlayer);
              }
              break;

            case SDLK_LEFT: //Aller à gauche
              nextCase = matriceMain((*rectanglePlayer).x-32, (*rectanglePlayer).y);
              if (nextCase!=0 && nextCase!=6){
                (*rectanglePlayer).x -= 32;
                if (updateMainGateDisplay (renderer, texture, rectangle, texturePlayer, rectanglePlayer))
                  return 1;
                if (nextCase > 2) {
                  if (randomAggro(font, renderer, nextCase, mysql))
                    return 1;
                }
              }else if(nextCase==6){
			manageHomeDisplay(renderer, texturePlayer);
              }
              break;

            case SDLK_SPACE: //Ouvrir menu
              manageMenuDisplay (texture, texturePlayer, renderer, rectangle, rectanglePlayer);
              if (updateMainGateDisplay (renderer, texture, rectangle, texturePlayer, rectanglePlayer))
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

int randomAggro (TTF_Font ** font, SDL_Renderer ** renderer, int nextCase, MYSQL * mysql) {

  int numRand;

  srand(time(NULL));
  numRand = 1;

  if(!numRand) {

    switch (nextCase) {
      case 3:
        if (randomChoseFight (font, renderer, mysql, "Roche"))
		return 1;
        break;

      case 4:
        if (randomChoseFight (font, renderer, mysql, "Eau"))
		return 1;
        break;

      case 5:
        if (randomChoseFight (font, renderer, mysql, "Plante"))
		return 1;
        break;

      default:
        break;
    }
  }

  return 0;
}

int randomChoseFight (TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, const char * type) {

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

	if (managefight(font, renderer, mysql, row))
		return 1;

	return 0;
}

int updateMainGateDisplay (SDL_Renderer ** renderer, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(texture, renderer, rectangle))
    return 1;

  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;

  return 0;
}

// manage error in homeDisplay
int manageMainGame (TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql) {

  SDL_Surface * map = NULL;
  SDL_Surface * surfacePlayer = NULL;
  SDL_Texture * texture = NULL;
  SDL_Texture * texturePlayer = NULL;

  int main = mainGameDisplay(font, &surfacePlayer, &texturePlayer, renderer, &map, &texture, mysql);
  closeMainGameDisplay(&map, &texture, &surfacePlayer, &texturePlayer);

  if (main)
    return 1;

  return 0;
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

int fightDisplay (SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, MYSQL * mysql, MYSQL_ROW row, SDL_Renderer ** renderer, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv) {

	Pokemon tab[6];
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

	if (loadDiplayPokemonPlayer(mysql, surfacePokemonPlayer, texturePokemonPlayer, renderer, &rectanglePokemonPlayer, tab[actu]))
		return 1;

	if (displayPvPokemon (text, textureText, font, black, tab[actu], 100, renderer, &rectangle))
		return 1;

	if (displayPvPokemon (text, textureText, font, black, adv, 1100, renderer, &rectangle))
		return 1;

	if (displayChoseActionFight(surfaceChoseActionFight, textureChoseActionFight, &rectangleChoseActionFight, surfaceCurseur, textureCurseur, &rectangleCurseur, renderer))
		return 1;

	if (manageEventChoseActionFight (surfaceSelect, textureSelect, textureChoseActionFight, &rectangleChoseActionFight, textureCurseur, &rectangleCurseur, renderer))
		return 1;

	return 0;
}

int manageEventChoseActionFight (SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer) {

	int curseur = 0;
	char poss = 0;
	SDL_bool programLaunched = SDL_TRUE;
	// event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
              programLaunched = SDL_FALSE; //fermer la map
              break;

            case SDLK_UP://Vers le haut
							poss += (poss - 2 < 0)?2:-2;
              break;

            case SDLK_DOWN://Vers le bas
							poss += (poss + 2 > 3)?-2:2;
              break;

            case SDLK_RIGHT://Aller à droite
							poss += (poss + 1 > 3)?-3:1;
              break;

            case SDLK_LEFT: //Aller à gauche
							poss += (poss - 1 < 0)?3:-1;
              break;

						case SDLK_w:
							switch (poss) {
								case 0: // fight
									break;

								case 1: // pokemon
									break;

								case 2: // item
									break;

								case 3:
									return 0;
									break;
							}
							break;

            default:
              break;
          }
	  			updateDisplayChoseActionFight (textureChoseActionFight, rectangleChoseActionFight, textureCurseur, rectangleCurseur, poss, renderer);
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

int displayPvPokemon (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Color black, Pokemon pokemonActu, int x, SDL_Renderer ** renderer, SDL_Rect * rectangle) {

	char * request;
	char * pvPokemon;
	char * pvActuPokemon;
	SDL_Rect rectangleText;

	pvPokemon = malloc(*pokemonActu.pv / 10 + 2);
	sprintf(pvPokemon, "%d", *pokemonActu.pv);

	pvActuPokemon = malloc(*pokemonActu.pvActuel / 10 + 2);
	sprintf(pvActuPokemon, "%d", *pokemonActu.pvActuel);

	request = malloc(strlen(pokemonActu.name) + strlen(pvPokemon) + strlen(pvActuPokemon) + strlen(" PV : /") + 1);

	strcpy(request, pokemonActu.name);
	strcat(request, " PV : ");
	strcat(request, pvActuPokemon);
	strcat(request, "/");
	strcat(request, pvPokemon);
	*text = TTF_RenderText_Blended(*font, request, black);

	free (pvPokemon);
	free (pvActuPokemon);
	free (request);
	if (displayAll(textureText, text, rectangle, renderer, x, 0, 400, -1))
		return 1;

	return 0;
}

int loadDiplayPokemonPlayer (MYSQL * mysql, SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, Pokemon pokemonActu) {

  char * request;
  int img;
  int i;
  double mul;

  request = malloc(strlen("../img/pokemon/.bmp") + strlen(pokemonActu.name) + 1);

  strcpy(request, "../img/pokemon/");
  strcat(request, pokemonActu.name);
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
  if (updateRenderer(texture, renderer, rectangle))
    return 1;

  return 0;
}

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

int takePokemonUser (MYSQL * mysql, Pokemon * tab) {

	int numRow;
	MYSQL_ROW row;
	MYSQL_RES *result;

	if (mysql_query(mysql, "SELECT NamePokemon, PV, Attack, Defense, Speed, lvl FROM POKEBALL WHERE IDTrainer=1 AND PC=0 ORDER BY LVL DESC")){
	    MySQL_PrintError("Error query", *mysql);
	    return 1;
	}

	result = mysql_store_result(mysql);
  if (result == NULL) {
    MySQL_PrintError("Error extract résult", *mysql);
		return 1;
  }

	for (int i = 0; i < 6; i++){
		row = mysql_fetch_row(result);
		if (row == NULL)
			return 0;
		strcpy(tab[i].name, row[0]);
		*tab[i].pv = atoi(row[1]) * atoi(row[5]);
		*tab[i].pvActuel = atoi(row[1]) * atoi(row[5]);
		*tab[i].attack = atoi(row[2]) * atoi(row[5]);
		*tab[i].defense = atoi(row[3]) * atoi(row[5]);
		*tab[i].speed = atoi(row[4]) * atoi(row[5]);
		*tab[i].lvl = atoi(row[5]);
	}

	return 0;
}

int takePokemonAdv (MYSQL * mysql, Pokemon * adv, int * lvlPlayer, MYSQL_ROW row) {

	int numRow;
	char * request;
	MYSQL_RES *result;
	int numRand;

  srand(time(NULL));
  *(*adv).lvl = rand()%(*lvlPlayer) + 1;

	request = malloc(strlen("SELECT Name, PV, Attack, Defense, Speed FROM POKEMON WHERE Name=''") + strlen(row[0]) + 1);
	strcpy(request, "SELECT Name, PV, Attack, Defense, Speed FROM POKEMON WHERE Name='");
	strcat(request, row[0]);
	strcat(request, "'");

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
	*(*adv).pv = atoi(row[1]) * *(*adv).lvl;
	*(*adv).pvActuel = atoi(row[1]) * *(*adv).lvl;
	*(*adv).attack = atoi(row[2]) * *(*adv).lvl;
	*(*adv).defense = atoi(row[3]) * *(*adv).lvl;
	*(*adv).speed = atoi(row[4]) * *(*adv).lvl;

	return 0;
}

// manage error in homeDisplay
int managefight (TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, MYSQL_ROW row) {

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

  int fight = fightDisplay(&surfaceSelect, &textureSelect, &surfaceChoseActionFight, &textureChoseActionFight, &surfaceCurseur, &textureCurseur, &text, &textureText, font, mysql, row, renderer, &surfaceBackground, &textureBackground, &surfacePokemonPlayer, &texturePokemonPlayer, &surfacePokemonAdv, &texturePokemonAdv);
  closeFightDisplay(&surfaceSelect, &textureSelect, &surfaceChoseActionFight, &textureChoseActionFight, &surfaceCurseur, &textureCurseur, &text, &textureText, &surfaceBackground, &textureBackground, &surfacePokemonPlayer, &texturePokemonPlayer, &surfacePokemonAdv, &texturePokemonAdv);

  if (fight)
    return 1;

  return 0;
}

// free surface and texture used in menu
void closeFightDisplay (SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv) {

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
*********************MENU********************
********************************************/

// Configuration Menu
int menuDisplay(SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur){

  SDL_Rect rectangleMenu;
  SDL_Rect rectangleCurseur;

  if (loadDiplayMenu (surfaceMenu, textureMenu, renderer, &rectangleMenu))
    return 1;

  // load personnage texture
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

        case SDLK_o:
        switch ((*rectangleCurseur).y){
                        case 355:
                        //go to Items
                        break;

                        case 430:
                        //save game
                        break;

                        case 505:
                        //go to Option
                        break;

                        case 580:
                        //exit menu
                        printf("exit");
                         programLaunched = SDL_FALSE;
                        break;

            }break;


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
int matriceHomeInt[12][20]={
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,0},
{0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
{0,1,1,0,0,2,0,2,0,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,1,1,0,0,1,1,3,1,1,0,0,1,1,1,1,1,0}
};
return matriceHomeInt[(y-90)/60][(x-200)/60];
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
(*rectanglePlayer).x = 220+60*9;
(*rectanglePlayer).y = 90+60*11;

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
  (*rectangleHome).h = 720;
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
                    managePcDisplay(renderer, texturePlayer, textureHome);
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
                    managePcDisplay(renderer, texturePlayer, textureHome);
              }else if(nextCase==3){
                   return 0;
              }
              break;

            case SDLK_RIGHT://Go to the Right
              nextCase = MatriceHome((*rectanglePlayer).x+60, (*rectanglePlayer).y);
              if (nextCase == 1){
                (*rectanglePlayer).x += 60;
                if (updateMainHomeDisplay (renderer, textureHome, rectangleHome, texturePlayer, rectanglePlayer))
                  return 1;
              }else if (nextCase==2){
                        managePcDisplay(renderer, texturePlayer, textureHome);
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
                    managePcDisplay(renderer, texturePlayer, textureHome);
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
int manageHomeDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer) {

  SDL_Surface * surfaceHome = NULL;
  SDL_Texture * textureHome = NULL;
  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  int home = homeDisplay(renderer, texturePlayer, &surfaceHome, &textureHome, &surfacePc, &texturePc);

  closeHomeDisplay(&surfaceHome, &textureHome, &surfacePc, &texturePc);

  if (home)
    return 1;

  return 0;
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
*********************PC********************
********************************************/

//Configuration Pc
int pcDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseurPc, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion){

  SDL_Rect rectanglePc;
  SDL_Rect rectangleCurseurPc;
  SDL_Rect rectanglePotion;
  SDL_Rect rectangleCurseurPotion;
  SDL_Rect rectanglePlayer;
  (rectanglePlayer).w=60;
  (rectanglePlayer).h=60;
  (rectanglePlayer).x = 220+60*9;
  (rectanglePlayer).y = 90+60*11;

  SDL_Rect rectangleHome;
  (rectangleHome).w=1200;
  (rectangleHome).h=720;
  (rectangleHome).x = (1600-(rectangleHome).w)/2;
  (rectangleHome).y = (900-(rectangleHome).h)/2;

  if (loadDiplayPc (surfacePc, texturePc, renderer, &rectanglePc))
    return 1;

  if (loadDiplayCurseurPc (surfaceCurseurPc, textureCurseurPc, renderer, &rectangleCurseurPc))
    return 1;

  if (manageEventPc (renderer, surfacePc, texturePc, &rectanglePc, surfaceCurseurPc, textureCurseurPc, &rectangleCurseurPc, texturePlayer, &rectanglePlayer, textureHome, &rectangleHome, texturePotion, textureCurseurPotion, &rectanglePotion, &rectangleCurseurPotion))
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
  (*rectangleCurseurPc).x = 325;
  (*rectangleCurseurPc).y = 480;

  // display texture
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;

  return 0;
}

// load and display pc
int loadDiplayPc (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc) {

  // load pc page
  if (loadBMP("../img/pcMenu.bmp", surfacePc))
    return 1;

  // create texture
  if (createTexture(texturePc, renderer, surfacePc))
    return 1;

  // load texture
  if (loadTexture(texturePc, rectanglePc))
    return 1;

  (*rectanglePc).w = 950;
  (*rectanglePc).h = 600;
  (*rectanglePc).x = (1500-(*rectanglePc).w)/2;
  (*rectanglePc).y = (800-(*rectanglePc).h)/2;

  // display texture
  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;

  return 0;
}


int manageEventPc (SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Rect * rectangleCurseurPc, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion) {

  SDL_bool programLaunched = SDL_TRUE;

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
                switch ((*rectangleCurseurPc).x){
                    case 325:
                        switch((*rectangleCurseurPc).y){
                            case 578:
                            (*rectangleCurseurPc).y-=98;

                        break;
                        }
                    break;

                    case 625:
                        switch((*rectangleCurseurPc).y){
                                case 578:
                                (*rectangleCurseurPc).y-=98;

                            break;
                                case 480:
                                (*rectangleCurseurPc).y-=98;
                            break;
                            }
                    break;
                }
              break;

            case SDLK_DOWN://Go Down
                switch((*rectangleCurseurPc).x){
                    case 325:
                        switch((*rectangleCurseurPc).y){
                                case 480:
                                (*rectangleCurseurPc).y+=98;
                            break;

                        }
                    break;

                    case 625:
                        switch((*rectangleCurseurPc).y){
                            case 382:
                                (*rectangleCurseurPc).y+=98;
                            break;
                                case 480:
                                (*rectangleCurseurPc).y+=98;
                            break;

                        }
                    break;
                }
              break;

            case SDLK_RIGHT://To the right
                switch((*rectangleCurseurPc).x){
                    case 325:
                    (*rectangleCurseurPc).x+=300;
                     break;
                }
              break;

            case SDLK_LEFT: //The left
                switch((*rectangleCurseurPc).x){

                    case 625:
                    switch((*rectangleCurseurPc).y){
                            case 578:
                                (*rectangleCurseurPc).x-=300;
                            break;
                                case 480:
                                (*rectangleCurseurPc).x-=300;
                            break;

                        }
                    break;
                }

            break;
            //Choose the option
            case SDLK_o:
                switch ((*rectangleCurseurPc).x){
                    case 625:
                      switch ((*rectangleCurseurPc).y){
                        case 382:
	                        managePotionDisplay (renderer, texturePlayer,textureHome);
                        break;
                        case 480:
                            manageReminderDisplay(renderer, texturePlayer, textureHome);
                        break;
                        case 578:
                            managePokeballsDisplay(renderer, texturePlayer, textureHome);
                        break;
                      }
                    break;
                }
            break;

            //Open menu
            case SDLK_SPACE:
              manageMenuDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc);
              if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc, texturePlayer, rectanglePlayer, textureHome, rectangleHome))
                return 1;
              break;

            default:
              break;
          }
          if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc, texturePlayer, rectanglePlayer, textureHome, rectangleHome))
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

// refresh pc
int updateMainPcDisplay (SDL_Texture ** texturePc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc, SDL_Rect * rectangleCurseurPc, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;
  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;


  return 0;
}

// manage error in pcDisplay
int managePcDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome) {

  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  SDL_Surface * surfaceCurseurPc = NULL;
  SDL_Texture * textureCurseurPc = NULL;
  SDL_Texture * texturePotion = NULL;
  SDL_Texture * textureCurseurPotion = NULL;


  int pc = pcDisplay(renderer, &surfacePc, &texturePc, &surfaceCurseurPc, &textureCurseurPc, texturePlayer, textureHome, &texturePotion, &textureCurseurPotion);

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

/*--------Potions--------*/
int potionDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePotion, SDL_Texture ** texturePotion, SDL_Surface ** surfaceCurseurPotion, SDL_Texture ** textureCurseurPotion, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome){

  SDL_Rect rectanglePotion;
  SDL_Rect rectangleCurseurPotion;
  SDL_Rect rectanglePlayer;

  SDL_Rect rectangleHome;

  if (loadDiplayPotion (surfacePotion, texturePotion, renderer, &rectanglePotion))
    return 1;

  if (loadDiplayCurseurPotion (surfaceCurseurPotion, textureCurseurPotion, renderer, &rectangleCurseurPotion))
    return 1;

  if (manageEventPotion (texturePotion, textureCurseurPotion, renderer, &rectanglePotion, &rectangleCurseurPotion, texturePlayer, &rectanglePlayer, textureHome, &rectangleHome))
    return 1;

  return 0;
}

int manageEventPotion (SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Renderer ** renderer, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

	SDL_bool programLaunched = SDL_TRUE;

	// event
	while (programLaunched) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {

						case SDLK_ESCAPE:
							programLaunched = SDL_FALSE; //Close the pcPotion
							break;
					}
					if (updateMainPotionDisplay (texturePotion, textureCurseurPotion, renderer, rectanglePotion, rectangleCurseurPotion, texturePlayer, rectanglePlayer, textureHome, rectangleHome))
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

// load and display curseur
int loadDiplayCurseurPotion (SDL_Surface ** surfaceCurseurPotion, SDL_Texture ** textureCurseurPotion, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPotion) {
  //CURSEUR
  // load curseur
  if (loadBMP("../img/curseur.bmp", surfaceCurseurPotion))
    return 1;
  if (displayAll (textureCurseurPotion, surfaceCurseurPotion, rectangleCurseurPotion, renderer, 325, 480, 25, 25))
    return 1;
  return 0;
}


// load and display pcPotion
int loadDiplayPotion (SDL_Surface ** surfacePotion, SDL_Texture ** texturePotion, SDL_Renderer ** renderer, SDL_Rect * rectanglePotion) {

  // load pcPotion
  if (loadBMP("../img/pcPotion.bmp", surfacePotion))
    return 1;
  if (displayAll (texturePotion, surfacePotion, rectanglePotion, renderer, 275, 100, 950, 600))
    return 1;
  return 0;
}

// refresh potion
int updateMainPotionDisplay (SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Renderer ** renderer, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;
  if (updateRenderer(texturePotion, renderer, rectanglePotion))
    return 1;
  if (updateRenderer(textureCurseurPotion, renderer, rectangleCurseurPotion))
    return 1;

  return 0;
}

// manage error in potionDisplay
int managePotionDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome) {

  SDL_Surface * surfacePotion = NULL;
  SDL_Texture * texturePotion = NULL;
  SDL_Surface * surfaceCurseurPotion = NULL;
  SDL_Texture * textureCurseurPotion = NULL;

  int potion = potionDisplay(renderer, &surfacePotion, &texturePotion, &surfaceCurseurPotion, &textureCurseurPotion, texturePlayer, textureHome);

  closePotionDisplay(&surfacePotion, &texturePotion, &surfaceCurseurPotion, &textureCurseurPotion);

  if (potion)
    return 1;

  return 0;
}

// free surface and texture used in potionDisplay
void closePotionDisplay (SDL_Surface ** surfacePotion, SDL_Texture ** texturePotion, SDL_Surface ** surfaceCurseurPotion, SDL_Texture ** textureCurseurPotion) {
  if (*surfacePotion != NULL)
    SDL_FreeSurface(*surfacePotion);
  if (*texturePotion != NULL)
    SDL_DestroyTexture(*texturePotion);
  if (*surfaceCurseurPotion != NULL)
    SDL_FreeSurface(*surfaceCurseurPotion);
  if (*textureCurseurPotion != NULL)
    SDL_DestroyTexture(*textureCurseurPotion);
}

/*--------Reminders--------*/

int reminderDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfaceReminder, SDL_Texture ** textureReminder, SDL_Surface ** surfaceCurseurReminder, SDL_Texture ** textureCurseurReminder, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome){

  SDL_Rect rectangleReminder;
  SDL_Rect rectangleCurseurReminder;
  SDL_Rect rectanglePlayer;
  SDL_Rect rectangleHome;

  if (loadDiplayReminder (surfaceReminder, textureReminder, renderer, &rectangleReminder))
    return 1;

  if (loadDiplayCurseurReminder (surfaceCurseurReminder, textureCurseurReminder, renderer, &rectangleCurseurReminder))
    return 1;

  if (manageEventReminder (textureReminder, textureCurseurReminder, renderer, &rectangleReminder, &rectangleCurseurReminder, texturePlayer, &rectanglePlayer, textureHome, &rectangleHome))
    return 1;

  return 0;
}

int manageEventReminder (SDL_Texture ** textureReminder, SDL_Texture ** textureCurseurReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleReminder, SDL_Rect * rectangleCurseurReminder, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

SDL_bool programLaunched = SDL_TRUE;

	// event
	while (programLaunched) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {

						case SDLK_ESCAPE:
							programLaunched = SDL_FALSE; //Close the pcReminder
							break;
					}
					if (updateMainReminderDisplay (textureReminder, textureCurseurReminder, renderer, rectangleReminder, rectangleCurseurReminder, texturePlayer, rectanglePlayer, textureHome, rectangleHome))
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


// load and display curseur
int loadDiplayCurseurReminder (SDL_Surface ** surfaceCurseurReminder, SDL_Texture ** textureCurseurReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurReminder) {
  //CURSEUR
  // load curseur
  if (loadBMP("../img/curseur.bmp", surfaceCurseurReminder))
    return 1;
  if (displayAll (textureCurseurReminder, surfaceCurseurReminder, rectangleCurseurReminder, renderer, 325, 480, 25, 25))
    return 1;
  return 0;
}


// load and display pcReminder
int loadDiplayReminder (SDL_Surface ** surfaceReminder, SDL_Texture ** textureReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleReminder) {

  // load pcReminder
  if (loadBMP("../img/pcRappel.bmp", surfaceReminder))
    return 1;
  if (displayAll (textureReminder, surfaceReminder, rectangleReminder, renderer, 275, 100, 950, 600))
    return 1;
  return 0;
}

// refresh pcReminder
int updateMainReminderDisplay (SDL_Texture ** textureReminder, SDL_Texture ** textureCurseurReminder, SDL_Renderer ** renderer, SDL_Rect * rectangleReminder, SDL_Rect * rectangleCurseurReminder, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;
  if (updateRenderer(textureReminder, renderer, rectangleReminder))
    return 1;
  if (updateRenderer(textureCurseurReminder, renderer, rectangleCurseurReminder))
    return 1;


  return 0;
}

// manage error in ReminderDisplay
int manageReminderDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome) {

  SDL_Surface * surfaceReminder = NULL;
  SDL_Texture * textureReminder = NULL;
  SDL_Surface * surfaceCurseurReminder = NULL;
  SDL_Texture * textureCurseurReminder = NULL;

  int reminder = reminderDisplay(renderer, &surfaceReminder, &textureReminder, &surfaceCurseurReminder, &textureCurseurReminder, texturePlayer, textureHome);

  closeReminderDisplay(&surfaceReminder, &textureReminder, &surfaceCurseurReminder, &textureCurseurReminder);

  if (reminder)
    return 1;

  return 0;
}

// free surface and texture used in ReminderDisplay
void closeReminderDisplay (SDL_Surface ** surfaceReminder, SDL_Texture ** textureReminder, SDL_Surface ** surfaceCurseurReminder, SDL_Texture ** textureCurseurReminder) {
  if (*surfaceReminder != NULL)
    SDL_FreeSurface(*surfaceReminder);
  if (*textureReminder != NULL)
    SDL_DestroyTexture(*textureReminder);
  if (*surfaceCurseurReminder != NULL)
    SDL_FreeSurface(*surfaceCurseurReminder);
  if (*textureCurseurReminder != NULL)
    SDL_DestroyTexture(*textureCurseurReminder);
}

/*--------Pokeballs--------*/
int pokeballsDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePokeballs, SDL_Texture ** texturePokeballs, SDL_Surface ** surfaceCurseurPokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome){

  SDL_Rect rectanglePokeballs;
  SDL_Rect rectangleCurseurPokeballs;
  SDL_Rect rectanglePlayer;
  (rectanglePlayer).w=60;
  (rectanglePlayer).h=60;
  (rectanglePlayer).x = 220+60*9;
  (rectanglePlayer).y = 90+60*11;

  SDL_Rect rectangleHome;
  (rectangleHome).w=1200;
  (rectangleHome).h=720;
  (rectangleHome).x = (1600-(rectangleHome).w)/2;
  (rectangleHome).y = (900-(rectangleHome).h)/2;

  if (loadDiplayPokeballs (surfacePokeballs, texturePokeballs, renderer, &rectanglePokeballs))
    return 1;

  if (loadDiplayCurseurPokeballs (surfaceCurseurPokeballs, textureCurseurPokeballs, renderer, &rectangleCurseurPokeballs))
    return 1;

  if (manageEventPokeballs (texturePokeballs, textureCurseurPokeballs, renderer, &rectanglePokeballs, &rectangleCurseurPokeballs, texturePlayer, &rectanglePlayer, textureHome, &rectangleHome))
    return 1;

  return 0;
}

int manageEventPokeballs (SDL_Texture ** texturePokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Renderer ** renderer, SDL_Rect * rectanglePokeballs, SDL_Rect * rectangleCurseurPokeballs, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome){
SDL_bool programLaunched = SDL_TRUE;
    
	// event
	while (programLaunched) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {

						case SDLK_ESCAPE:
							programLaunched = SDL_FALSE; //Close the pcPokeballs
							break;
					}
					if (updateMainPokeballsDisplay (texturePokeballs, textureCurseurPokeballs, renderer, rectanglePokeballs, rectangleCurseurPokeballs, texturePlayer, rectanglePlayer, textureHome, rectangleHome))
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


// load and display curseur
int loadDiplayCurseurPokeballs (SDL_Surface ** surfaceCurseurPokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPokeballs) {
  //CURSEUR
  // load curseur
  if (loadBMP("../img/curseur.bmp", surfaceCurseurPokeballs))
    return 1;
  if (displayAll (textureCurseurPokeballs, surfaceCurseurPokeballs, rectangleCurseurPokeballs, renderer, 325, 480, 25, 25))
    return 1;
  return 0;
}


// load and display pcPokeballs
int loadDiplayPokeballs (SDL_Surface ** surfacePokeballs, SDL_Texture ** texturePokeballs, SDL_Renderer ** renderer, SDL_Rect * rectanglePokeballs) {

  // load pc Pokeballs
  if (loadBMP("../img/pcPokeball.bmp", surfacePokeballs))
    return 1;
  if (displayAll (texturePokeballs, surfacePokeballs, rectanglePokeballs, renderer, 275, 100, 950, 600))
    return 1;
  return 0;
}


// refresh pcPokeballs
int updateMainPokeballsDisplay (SDL_Texture ** texturePokeballs, SDL_Texture ** textureCurseurPokeballs, SDL_Renderer ** renderer, SDL_Rect * rectanglePokeballs, SDL_Rect * rectangleCurseurPokeballs, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;
  if (updateRenderer(texturePokeballs, renderer, rectanglePokeballs))
    return 1;
  if (updateRenderer(textureCurseurPokeballs, renderer, rectangleCurseurPokeballs))
    return 1;


  return 0;
}

// manage error in PokeballsDisplay
int managePokeballsDisplay (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Texture ** textureHome) {

  SDL_Surface * surfacePokeballs = NULL;
  SDL_Texture * texturePokeballs = NULL;
  SDL_Surface * surfaceCurseurPokeballs = NULL;
  SDL_Texture * textureCurseurPokeballs = NULL;

  int pokeballs = pokeballsDisplay(renderer, &surfacePokeballs, &texturePokeballs, &surfaceCurseurPokeballs, &textureCurseurPokeballs, texturePlayer, textureHome);

  closePokeballsDisplay(&surfacePokeballs, &texturePokeballs, &surfaceCurseurPokeballs, &textureCurseurPokeballs);

  if (pokeballs)
    return 1;

  return 0;
}

// free surface and texture used in PokeballsDisplay
void closePokeballsDisplay (SDL_Surface ** surfacePokeballs, SDL_Texture ** texturePokeballs, SDL_Surface ** surfaceCurseurPokeballs, SDL_Texture ** textureCurseurPokeballs) {
  if (*surfacePokeballs != NULL)
    SDL_FreeSurface(*surfacePokeballs);
  if (*texturePokeballs != NULL)
    SDL_DestroyTexture(*texturePokeballs);
  if (*surfaceCurseurPokeballs != NULL)
    SDL_FreeSurface(*surfaceCurseurPokeballs);
  if (*textureCurseurPokeballs != NULL)
    SDL_DestroyTexture(*textureCurseurPokeballs);
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
