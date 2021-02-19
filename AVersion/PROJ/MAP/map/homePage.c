#include "homePage.h"

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

	SDL_RenderPresent(*renderer);

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

	SDL_RenderPresent(*renderer);

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
