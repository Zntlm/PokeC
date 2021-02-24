#include "buy.h"

int buyDisplay (SDL_Surface ** textPokeDollar, SDL_Texture ** texturePokeDollar, MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy) {

  SDL_Rect rectangleBuy;
  int cost = 0;
  int PokeDollar = 0;
  MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;
	SDL_Rect rectangle;
	SDL_Color black = {0, 0, 0};

  request = malloc(strlen("SELECT PokeDollar FROM TRAINER WHERE ID=1") + 1);
  strcpy(request, "SELECT PokeDollar FROM TRAINER WHERE ID=1");

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

  PokeDollar = atoi(row[0]);

  if (!strcmp(item, "../img/pcPotion.bmp")) {
    cost = 1000;
  } else if (!strcmp(item, "../img/pcRappel.bmp")) {
    cost = 1500;
  } else if (!strcmp(item, "../img/pcPokeball.bmp")) {
    cost = 500;
  }

  if (loadBMP(item, surfaceBuy))
    return 1;

  if (displayAll(textureBuy, surfaceBuy, &rectangleBuy, renderer, 0, 0, 1600, 900))
    return 1;

  if (displayNumber (cost, 0, text, textureText, font, renderer))
    return 1;

  request = malloc(strlen("PokeDollar : ") + sizeof(int) + 1);
  sprintf(request, "PokeDollar : %d", PokeDollar);

  *textPokeDollar = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(texturePokeDollar, textPokeDollar, &rectangle, renderer, 700, 800, -1, -1))
		return 1;

  SDL_RenderPresent(*renderer);

  if (manageEventBuy (PokeDollar, texturePokeDollar, &rectangle, cost, mysql, text, textureText, font, config, renderer, textureBuy, &rectangleBuy))
    return 1;

  return 0;
}

int manageEventBuy (int pokeDollar, SDL_Texture ** texturePokeDollar, SDL_Rect * rectangle, int cost, MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectangleBuy) {

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

            if (number < pokeDollar/cost)
              number++;

					} else if (event.key.keysym.sym == config.down) {

            if (number > 0)
              number--;

					} else if (event.key.keysym.sym == config.validate) {

            if (number != 0)
              buy(mysql, cost, number, pokeDollar);
            return 0;

					}
    			if (updateBuy (texturePokeDollar, rectangle, cost, number, text, textureText, font, renderer, textureBuy, rectangleBuy))
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

int buy (MYSQL * mysql, int cost, int number, int pokeDollar) {

  MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;
  char * item;

  if (cost == 500) {
    item = malloc (strlen("Pokeball") + 1);
    sprintf(item, "Pokeball");
  } else if (cost == 1000) {
    item = malloc (strlen("Potion") + 1);
    sprintf(item, "Potion");
  } else if (cost == 1500) {
    item = malloc (strlen("Revive") + 1);
    sprintf(item, "Revive");
  }

  request = malloc(strlen("SELECT  FROM TRAINER WHERE ID=1") + strlen(item) + 1);
  sprintf(request, "SELECT %s FROM TRAINER WHERE ID=1", item);

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

  request = malloc(strlen("UPDATE TRAINER SET = ,PokeDollar= WHERE ID=1") + strlen(item) + sizeof(int) * 2 + 1);
  sprintf(request, "UPDATE TRAINER SET %s=%d ,PokeDollar=%d WHERE ID=1", item, atoi(row[0]) + number, pokeDollar - number * cost);

  if (mysql_query(mysql, request)){
      free(request);
      MySQL_PrintError("Error query", *mysql);
      return 1;
  }
  free(request);

  return 0;
}

int displayNumber (int cost, int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer) {

  char * request;
	SDL_Rect rectangle;
	SDL_Color black = {0, 0, 0};

  request = malloc( sizeof(int) * 2 + strlen(" x  PokeDollar") + 1);
  sprintf(request, "%d x %d PokeDollar", number, cost);

  *text = TTF_RenderText_Blended(*font, request, black);

  free (request);
  if (displayAll(textureText, text, &rectangle, renderer, 800, 550, -1, -1))
    return 1;

  return 0;
}

int updateBuy (SDL_Texture ** texturePokeDollar, SDL_Rect * rectangle, int cost, int number, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Texture ** textureBuy, SDL_Rect * rectanglebuy) {

  if (updateRenderer(textureBuy, renderer, rectanglebuy))
    return 1;

  if (displayNumber (cost, number, text, textureText, font, renderer))
    return 1;

  if (updateRenderer(texturePokeDollar, renderer, rectangle))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int manageBuy (MYSQL * mysql, TTF_Font ** font, const char * item, Config config, SDL_Renderer ** renderer) {

  SDL_Surface * surfaceBuy = NULL;
  SDL_Texture * textureBuy = NULL;
  SDL_Surface * text = NULL;
  SDL_Texture * textureText = NULL;
  SDL_Surface * textPokeDollar = NULL;
  SDL_Texture * texturePokeDollar = NULL;

  int buy = buyDisplay(&textPokeDollar, &texturePokeDollar, mysql, &text, &textureText, font, item, config, renderer, &surfaceBuy, &textureBuy);

  closeBuy(&textPokeDollar, &texturePokeDollar, &text, &textureText, &surfaceBuy, &textureBuy);

  return buy;
}

void closeBuy (SDL_Surface ** textPokeDollar, SDL_Texture ** texturePokeDollar, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBuy, SDL_Texture ** textureBuy) {

  if (*surfaceBuy != NULL)
    SDL_FreeSurface(*surfaceBuy);
  if (*textureBuy != NULL)
    SDL_DestroyTexture(*textureBuy);
  if (*text != NULL)
    SDL_FreeSurface(*text);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);
  if (*textPokeDollar != NULL)
    SDL_FreeSurface(*textPokeDollar);
  if (*texturePokeDollar != NULL)
    SDL_DestroyTexture(*texturePokeDollar);

}
