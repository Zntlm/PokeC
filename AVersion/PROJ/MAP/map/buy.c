#include "buy.h"

int buyDisplay (MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy) {

  SDL_Rect rectangleBuy;

  if (loadBMP(item, surfaceBuy))
    return 1;

  if (displayAll(textureBuy, surfaceBuy, &rectangleBuy, renderer, 0, 0, 1600, 900))
    return 1;

  if (displayNumber (0, text, textureText, font, renderer))
    return 1;

  SDL_RenderPresent(*renderer);

  if (manageEventBuy (mysql, text, textureText, font, config, renderer, textureBuy, &rectangleBuy))
    return 1;

  return 0;
}

int manageEventBuy (MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectangleBuy) {

  SDL_bool programLaunched = SDL_TRUE;
  int number = 0;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

            number++;

					} else if (event.key.keysym.sym == config.down) {

            if (number > 0)
              number--;

					} else if (event.key.keysym.sym == config.validate) {



					}
    			if (updateBuy (number, text, textureText, font, renderer, textureBuy, rectangleBuy))
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

int displayNumber (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer) {

  char * request;
	SDL_Rect rectangle;
	SDL_Color black = {0, 0, 0};

  request = malloc( sizeof(int) + 1);
  sprintf(request, "%d x 1500 PokeDollard", number);

  *text = TTF_RenderText_Blended(*font, request, black);

  free (request);
  if (displayAll(textureText, text, &rectangle, renderer, 800, 550, -1, -1))
    return 1;

  return 0;
}

int updateBuy (int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectanglebuy) {

  if (updateRenderer(textureBuy, renderer, rectanglebuy))
    return 1;

  if (displayNumber (number, text, textureText, font, renderer))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int manageBuy (MYSQL * mysql, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer) {

  SDL_Surface * surfaceBuy = NULL;
  SDL_Texture * textureBuy = NULL;
  SDL_Surface * text = NULL;
  SDL_Texture * textureText = NULL;

  int buy = buyDisplay(mysql, &text, &textureText, font, item, config, renderer, &surfaceBuy, &textureBuy);

  closeBuy(&text, &textureText, &surfaceBuy, &textureBuy);

  return buy;
}

void closeBuy (SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy) {

  if (*surfaceBuy != NULL)
    SDL_FreeSurface(*surfaceBuy);
  if (*textureBuy != NULL)
    SDL_DestroyTexture(*textureBuy);
  if (*text != NULL)
    SDL_FreeSurface(*text);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);

}
