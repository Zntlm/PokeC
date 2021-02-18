#include <SDL.h>
#include <stdio.h>
#include <mysql.h>
#include "create.h"

// laod BMP
int loadBMP (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, MYSQL * mysql, const char * img, SDL_Surface ** surface) {

	// load img
	*surface = SDL_LoadBMP(img);
	if (*surface == NULL) {
		SDL_PrintError("Error loading image");
		CloseSDLMySQL(texture, renderer, window, mysql);
		return 1;
	}

	return 0;
}

// create texture
int createTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, MYSQL * mysql, SDL_Surface ** surface) {

	*texture = SDL_CreateTextureFromSurface(*renderer, *surface);
	if (*texture == NULL) {
		SDL_PrintError("Error create texture");
		CloseSDLMySQL(texture, renderer, window, mysql);
		return 1;
	}

	return 0;
}

// load texture
int loadTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, MYSQL * mysql, int x, int y, SDL_Rect * rectangle) {

	// load texture
	if(SDL_QueryTexture(*texture, NULL, NULL, &(*rectangle).w, &(*rectangle).h) != 0){
		SDL_PrintError("Error loading texture");
		CloseSDLMySQL(texture, renderer, window, mysql);
		return 1;
	}

	// define texture poss
	(*rectangle).x = x;
	(*rectangle).y = y;

	return 0;
}

// reload renderer
int updateRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, MYSQL * mysql, SDL_Rect * rectangle) {

	// copy texture
	if(SDL_RenderCopy(*renderer, *texture, NULL, rectangle)){
		SDL_PrintError("Error display texture");
		CloseSDLMySQL(texture, renderer, window, mysql);
		return 1;
	}

	// update renderer
	SDL_RenderPresent(*renderer);

	return 0;
}

// start SDL
int initSDL (MYSQL * mysql) {

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		SDL_PrintError("Error init SDL");
		mysql_close(mysql);
		return 1;
	}

	return 0;
}

// create renderer
int createRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, MYSQL * mysql) {

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
	if (*renderer == NULL) {
		SDL_PrintError("Error create renderer");
		CloseSDLMySQL(texture, renderer, window, mysql);
		return 1;
	}

	return 0;
}

// create window
int createWindow (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, MYSQL * mysql, int x, int y) {

	*window = SDL_CreateWindow("pokemon 20/20", 0, 0, x, y, SDL_WINDOW_FULLSCREEN);
	if (*window == NULL) {
		SDL_PrintError("Error create window");
		CloseSDLMySQL(texture, renderer, window, mysql);
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
		mysql_close(mysql);
		return 1;
	}
	return 0;
}

// display error SDL
void SDL_PrintError(const char * message) {

	printf("%s : %s\n", message, SDL_GetError());
}

void MySQL_PrintError(const char * message, MYSQL mysql) {

	printf("%s : %d > %s\n", message, mysql_errno(&mysql), mysql_error(&mysql));
}

// close SDL and MySQL
void CloseSDLMySQL(SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, MYSQL * mysql){

	if (*texture != NULL) {
		SDL_DestroyTexture(*texture);
	} if (*renderer != NULL) {
		SDL_DestroyRenderer(*renderer);
	} if (*window != NULL) {
		SDL_DestroyWindow(*window);
	}
	SDL_Quit();
	mysql_close(mysql);
}

// diplay version SDL and MySQL
void version () {

	SDL_version nb;
	SDL_VERSION(&nb);
	printf("SDL : %d.%d.%d !\n", nb.major, nb.minor, nb.patch);
	printf("MySQL client version : %s\n", mysql_get_client_info());
}
