#include <SDL.h>
#include <stdio.h>
#include <mysql.h>
#include "create.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main (int argc, char ** argv) {

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Texture * texture = NULL;
	SDL_Rect rectangle;
	SDL_bool programLaunched = SDL_TRUE;
	SDL_Surface * home = NULL;
	SDL_Surface * exit = NULL;
	SDL_Surface * pointer = NULL;
	MYSQL mysql;

	// display version SDL and MySQL
	version();

	// init MySQL and connect database
	if (connectDataBase(&mysql))
		return 0;

	// start SDL
	if (initSDL(&mysql))
		return 0;

	// create Window
	if (createWindow(&texture, &renderer, &window, &mysql, WINDOW_WIDTH, WINDOW_HEIGHT))
		return 0;

	// createRenderer
	if (createRenderer(&texture, &renderer, &window, &mysql))
		return 0;

	// load home page
	if (loadBMP(&texture, &renderer, &window, &mysql, "img/Home.bmp", &home))
		return 0;

	// create texture
	if (createTexture(&texture, &renderer, &window, &mysql, &home))
		return 0;

	// load texture
	if (loadTexture(&texture, &renderer, &window, &mysql, (WINDOW_WIDTH - (*home).w)/2, (WINDOW_HEIGHT - (*home).h)/2, &rectangle))
		return 0;

	// display texture
	if (updateRenderer(&texture, &renderer, &window, &mysql, &rectangle))
		return 0;

	// load pointer
	if (loadBMP(&texture, &renderer, &window, &mysql, "img/pointer.bmp", &pointer))
		return 0;

	// create texture
	if (createTexture(&texture, &renderer, &window, &mysql, &pointer))
		return 0;

	// load texture
	if (loadTexture(&texture, &renderer, &window, &mysql, (WINDOW_WIDTH - (*pointer).w)/2, 400, &rectangle))
		return 0;

	// display texture
	if (updateRenderer(&texture, &renderer, &window, &mysql, &rectangle))
		return 0;

	// event
	while (programLaunched) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {

						case SDLK_ESCAPE:
							programLaunched = SDL_FALSE;
							break;

						default:
							continue;
					}

				case SDL_QUIT:
					programLaunched = SDL_FALSE;
					break;

				default:
					break;
			}
		}
	}

	// close SDL and database
	CloseSDLMySQL(&texture, &renderer, &window, &mysql);

	return 0;
}
