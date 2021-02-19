#include "config.h"

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
