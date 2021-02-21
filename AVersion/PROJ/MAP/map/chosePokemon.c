#include "chosePokemon.h"

int switchDisplay (Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer) {

	SDL_Rect rectangleCurseur;
	SDL_Rect rectangleSwitch;
	SDL_Rect rectangle[6];
	int number = 0;

	while (strcmp(player[number].name, "")) {
		number++;
	}
	number--;

	if (loadBMP("../img/chosePokemon.bmp", surfaceSwitch))
    return 1;

  if (displayAll(textureSwitch, surfaceSwitch, &rectangleSwitch, renderer, 0, 0, 1600, 900))
    return 1;

	if (displaySixPokemon (number, text, textureText, font, player, rectangle, surfacePokemon, renderer))
		return 1;

  if (loadBMP("../img/curseur.bmp", surfaceCurseur))
    return 1;

  if (displayAll(textureCurseur, surfaceCurseur, &rectangleCurseur, renderer, 10, 110, 25, 25))
    return 1;

	SDL_RenderPresent(*renderer);

	return manageSwitchPokemonDisplay (number, config, text, textureText, font, &rectangleCurseur, &rectangleSwitch, rectangle, player, surfacePokemon, surfaceCurseur, textureCurseur, surfaceSwitch, textureSwitch, renderer);
}

int manageSwitchPokemonDisplay (int number, Config config, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer) {

	SDL_bool programLaunched = SDL_TRUE;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						(*rectangleCurseur).y -= ((*rectangleCurseur).y == 110) ? - 80 * number : 80;

					} else if (event.key.keysym.sym == config.down) {

						(*rectangleCurseur).y += ((*rectangleCurseur).y == 110 + 80 * number) ? - 80 * number : 80;

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
			if (updatePokeball (number, text, textureText, font, rectangleCurseur, rectangleSwitch, rectangle, player, surfacePokemon, surfaceCurseur, textureCurseur, surfaceSwitch, textureSwitch, renderer))
				return 1;
    }
  }

  return 0;
}

int updatePokeball (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Rect * rectangleCurseur, SDL_Rect * rectangleSwitch, SDL_Rect rectangle[6], Pokemon player[6], SDL_Surface ** surfacePokemon, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfaceSwitch, SDL_Texture ** textureSwitch, SDL_Renderer ** renderer) {

	if (updateRenderer(textureSwitch, renderer, rectangleSwitch))
		return 1;

	if (displaySixPokemon (number, text, textureText, font, player, rectangle, surfacePokemon, renderer))
		return 1;

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	SDL_RenderPresent(*renderer);

	return 0;
}

int displaySixPokemon (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Pokemon player[6], SDL_Rect rectangle[6], SDL_Surface ** surfacePokemon, SDL_Renderer ** renderer) {

	char * request;
	SDL_Rect rectanglePV;
	SDL_Color black = {0, 0, 0};

	for (int i = 0; i <= number; i++) {

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

	SDL_RenderPresent(*renderer);

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
