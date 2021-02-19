#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <mysql.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

void SDL_PrintError (const char * message);
void MySQL_PrintError (const char * message, MYSQL mysql);
void CloseSDLMySQL (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql);
void version ();
int connectDataBase (MYSQL * mysql);
int initSDL (MYSQL * mysql);
int createWindow (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, int x, int y);
int createRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql);
int loadBMP (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, const char * img, SDL_Surface ** surface);
int createTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, SDL_Surface ** surface);
int loadTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, int x, int y, SDL_Rect * rectangle);
int updateRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, SDL_Rect * rectangle);
int defineKey (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql);
int configKey (int * escape, int * validate, int * cancel, int * up, int * down, int * right, int * left, int * inventory, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql);
int pressedKey ();
int displayHomePage (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql);
int displayExit (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, int keyValidate, int keyCancel);


int main (int argc, char ** argv) {

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Texture * texture = NULL;
	SDL_Surface * texte = NULL;
	SDL_Rect rectangle;
	TTF_Font * font = NULL;
	SDL_Color couleurNoire = {255, 255, 255};
	SDL_bool programLaunched = SDL_TRUE;
	MYSQL mysql;
	int keyEscape;
	int keyValidate;
	int keyCancel;
	int keyUp;
	int keyDown;
	int keyRight;
	int keyLeft;
	int keyInventory;
	int exit;

	// Display version SDL and MySQL
	version();

	// Init MySQL and connect database
	if (connectDataBase(&mysql))
		return 0;

	// Start SDL
	if (initSDL(&mysql))
		return 0;

	// Create Window
	if (createWindow(&texture, &renderer, &window, &font, &mysql, WINDOW_WIDTH, WINDOW_HEIGHT))
		return 0;

	// Create Renderer
	if (createRenderer(&texture, &renderer, &window, &font, &mysql))
		return 0;

	// Configure key
	if (configKey(&keyEscape, &keyValidate, &keyCancel, &keyUp, &keyDown, &keyRight, &keyLeft, &keyInventory, &texture, &renderer, &window, &font, &mysql))
		return 0;

	// Display home page
	if (displayHomePage(&texture, &renderer, &window, &font, &mysql))
		return 0;

	// Event
	while (programLaunched) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_KEYDOWN:

					if (event.key.keysym.sym == keyEscape) {
						// Display exit menu
						exit = displayExit(&texture, &renderer, &window, &font, &mysql, keyValidate, keyCancel);
						if (exit == 1){
							return 0;
						} else if (exit == 2) {
							programLaunched = SDL_FALSE;
						}
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

	// close SDL and database
	CloseSDLMySQL(&texture, &renderer, &window, &font, &mysql);

	return 0;
}

int displayExit (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, int keyValidate, int keyCancel) {

	SDL_Surface * home = NULL;
	SDL_Rect rectangle;

	// load home page
	if (loadBMP(texture, renderer, window, font, mysql, "img/exit.bmp", &home))
		return 1;

	// create texture
	if (createTexture(texture, renderer, window, font, mysql, &home))
		return 1;

	// load texture
	if (loadTexture(texture, renderer, window, font, mysql, 0, 0, &rectangle))
		return 1;

	// display texture
	if (updateRenderer(texture, renderer, window, font, mysql, &rectangle))
		return 1;

	// Event
	while (1) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_KEYDOWN:

					if (event.key.keysym.sym == keyValidate) {
						return 2;
					} else if (event.key.keysym.sym == keyCancel) {
						return 0;
					}
					break;

				case SDL_QUIT:
					return 2;
					break;

				default:
					break;
			}
		}
	}

	return 0;
}

int displayHomePage (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql) {

	SDL_Surface * home = NULL;
	SDL_Rect rectangle;

	// load home page
	if (loadBMP(texture, renderer, window, font, mysql, "img/Home.bmp", &home))
		return 1;

	// create texture
	if (createTexture(texture, renderer, window, font, mysql, &home))
		return 1;

	// load texture
	if (loadTexture(texture, renderer, window, font, mysql, 0, 0, &rectangle))
		return 1;

	// display texture
	if (updateRenderer(texture, renderer, window, font, mysql, &rectangle))
		return 1;

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

	return 0;
}

// configure player keys
int configKey (int * escape, int * validate, int * cancel, int * up, int * down, int * right, int * left, int * inventory, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql) {

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
			if (defineKey(texture, renderer, window, font, mysql))
				return 1;
			fseek(fileConfig, 0, SEEK_SET);
		}

		while (!feof(fileConfig) && count < 8) {

			fscanf(fileConfig, "%s : %d\n", nameKey, &key);

			if (strcmp(nameKey, "escape") == 0) {
				*escape = key;
				count++;
			} else if (strcmp(nameKey,"validate") == 0) {
				*validate = key;
				count++;
			} else if (strcmp(nameKey, "cancel") == 0) {
				*cancel = key;
				count++;
			} else if (strcmp(nameKey, "up") == 0) {
				*up = key;
				count++;
			} else if (strcmp(nameKey, "down") == 0) {
				*down = key;
				count++;
			} else if (strcmp(nameKey, "right") == 0) {
				*right = key;
				count++;
			} else if (strcmp(nameKey, "left") == 0) {
				*left = key;
				count++;
			} else if (strcmp(nameKey, "inventory") == 0) {
				*inventory = key;
				count++;
			}
		}

		if (count < 8) {
			if (defineKey(texture, renderer, window, font, mysql))
				return 1;
		}
	}

	fclose(fileConfig);
	return 0;
}

int defineKey (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql) {

	FILE * fileConfig;
	SDL_Rect rectangle;
	SDL_Surface * page = NULL;
	int key;
	char nameAction[8][20] = {"escape", "validate", "cancel", "up", "down", "right", "left", "inventory"};
	char nameFile[8][30] = {"img/quitter.bmp", "img/valider.bmp", "img/annuler.bmp", "img/haut.bmp", "img/bas.bmp", "img/droite.bmp", "img/gauche.bmp", "img/inventaire.bmp"};

	fileConfig = fopen("config.dat", "r+b");

	fprintf(fileConfig, "KEY:\n");

	for (int i = 0; i < 8; i++) {

		// load home page
		if (loadBMP(texture, renderer, window, font, mysql, nameFile[i], &page))
			return 1;

		// create texture
		if (createTexture(texture, renderer, window, font, mysql, &page))
			return 1;

		// load texture
		if (loadTexture(texture, renderer, window, font, mysql, 0, 0, &rectangle))
			return 1;

		// display texture
		if (updateRenderer(texture, renderer, window, font, mysql, &rectangle))
			return 1;

		key = pressedKey();
		fprintf(fileConfig, "%s : %d\n", nameAction[i], key);
	}

	fclose(fileConfig);

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

// laod BMP
int loadBMP (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, const char * img, SDL_Surface ** surface) {

	// load img
	*surface = SDL_LoadBMP(img);
	if (*surface == NULL) {
		SDL_PrintError("Error loading image");
		CloseSDLMySQL(texture, renderer, window, font, mysql);
		return 1;
	}

	return 0;
}

// create texture
int createTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, SDL_Surface ** surface) {

	*texture = SDL_CreateTextureFromSurface(*renderer, *surface);
	if (*texture == NULL) {
		SDL_PrintError("Error create texture");
		CloseSDLMySQL(texture, renderer, window, font, mysql);
		return 1;
	}

	return 0;
}

// load texture
int loadTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, int x, int y, SDL_Rect * rectangle) {

	// load texture
	if(SDL_QueryTexture(*texture, NULL, NULL, &(*rectangle).w, &(*rectangle).h) != 0){
		SDL_PrintError("Error loading texture");
		CloseSDLMySQL(texture, renderer, window, font, mysql);
		return 1;
	}

	// define texture poss
	(*rectangle).x = x;
	(*rectangle).y = y;

	return 0;
}

// reload renderer
int updateRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, SDL_Rect * rectangle) {

	// copy texture
	if(SDL_RenderCopy(*renderer, *texture, NULL, rectangle)){
		SDL_PrintError("Error display texture");
		CloseSDLMySQL(texture, renderer, window, font, mysql);
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

	// init SDL_ttf
	if (TTF_Init() == -1) {
		SDL_PrintError("Error init SDL_ttf");
		mysql_close(mysql);
		return 1;
	}

	return 0;
}

// create renderer
int createRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql) {

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
	if (*renderer == NULL) {
		SDL_PrintError("Error create renderer");
		CloseSDLMySQL(texture, renderer, window, font, mysql);
		return 1;
	}

	return 0;
}

// create window
int createWindow (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql, int x, int y) {

	*window = SDL_CreateWindow("pokemon 20/20", 0, 0, x, y, SDL_WINDOW_FULLSCREEN);
	if (*window == NULL) {
		SDL_PrintError("Error create window");
		CloseSDLMySQL(texture, renderer, window, font, mysql);
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
	if (!mysql_real_connect(mysql, "localhost", "partiel", "azerty", "pokemon", 80, NULL, 0)) {
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
void CloseSDLMySQL(SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Window ** window, TTF_Font ** font, MYSQL * mysql){

	if (*texture != NULL) {
		SDL_DestroyTexture(*texture);
	} if (*renderer != NULL) {
		SDL_DestroyRenderer(*renderer);
	} if (*window != NULL) {
		SDL_DestroyWindow(*window);
	} if (*font != NULL) {
		TTF_CloseFont(*font);
	}
	TTF_Quit();
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
