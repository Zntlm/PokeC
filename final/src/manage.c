#include "manage.h"

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
  //SDL_RenderPresent(*renderer);

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
