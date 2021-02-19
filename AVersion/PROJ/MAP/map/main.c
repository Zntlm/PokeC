#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql/mysql.h>
#include "types.h"
#include "homePage.h"

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
