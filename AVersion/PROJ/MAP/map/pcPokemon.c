#include "pcPokemon.h"

int displayPc (SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc) {

  SDL_Rect rectanglePc;
  SDL_Rect rectangleCurseur;
  int number;

  if (loadBMP("../img/pcMenu.bmp", surfacePc))
    return 1;

  if (displayAll(texturePc, surfacePc, &rectanglePc, renderer, 0, 0, 1600, 900))
    return 1;

  if (selectPokemon (&number, mysql, listPokemon))
    return 1;

  if (displayPokemon (surfacePokemon, 0, (number > 9*5)? 9*5 : number, listPokemon, renderer))
    return 1;

  if (loadBMP("../img/curseurPcPokemon.bmp", surfaceCurseur))
    return 1;

  if (displayAll(textureCurseur, surfaceCurseur, &rectangleCurseur, renderer, 600, 350, 100, 100))
    return 1;

  SDL_RenderPresent(*renderer);

  return managePc(textureCurseur, &rectangleCurseur, number, surfacePokemon, listPokemon, config, texturePc, &rectanglePc, renderer);
}

int selectPokemon (int * number, MYSQL * mysql, Pokemon ** listPokemon) {

  MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;
  int i = 0;

  request = malloc(strlen("SELECT ID, LVL, XP, NamePokemon FROM POKEBALL WHERE IDTrainer=1 AND PC=1") + 1);
  strcpy(request, "SELECT ID, LVL, XP, NamePokemon FROM POKEBALL WHERE IDTrainer=1 AND PC=1");

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

  *number = mysql_num_rows(result);
  *listPokemon = malloc(sizeof(Pokemon) * *number);

  while ((row = mysql_fetch_row(result))) {

    strcpy((*listPokemon)[i].id, row[0]);
    (*listPokemon)[i].lvl = atoi(row[1]);
    (*listPokemon)[i].xp = atoi(row[2]);
    strcpy((*listPokemon)[i].name, row[3]);
    (*listPokemon)[i].img = NULL;
    i++;
  }

  return 0;
}

int displayPokemon (SDL_Surface ** surfacePokemon, int min, int max, Pokemon ** listPokemon, SDL_Renderer ** renderer) {

  int i;
  char * request;
  SDL_Rect rectangle;
  rectangle.w = 100;
  rectangle.h = 100;

  for (i = min; i < max; i++) {
    if ((*listPokemon)[i].img == NULL) {

      request = malloc(strlen("../img/pokemon/.bmp") + strlen((*listPokemon)[i].name) + 1);
      sprintf(request, "../img/pokemon/%s.bmp", (*listPokemon)[i].name);

      if (loadBMP(request, surfacePokemon)){
        free(request);
        return 1;
      }
      free(request);

      if (displayAll(&((*listPokemon)[i].img), surfacePokemon, &rectangle, renderer, ((i - min) % 9) * 100 + 600, ((i - min) / 9) * 100 + 350, 100, 100))
        return 1;
    } else {
      rectangle.x = ((i - min) % 9) * 100 + 600;
      rectangle.y = ((i - min) / 9) * 100 + 350;
      if (updateRenderer(&((*listPokemon)[i].img), renderer, &rectangle))
        return 1;
    }
  }

  return 0;
}

int managePc (SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int number, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, Config config, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer) {

  SDL_bool programLaunched = SDL_TRUE;
  int min = 0;
  int max = (number > 9*5)? 9*5 : number;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

            if (number >= 9 *5){
              (*rectangleCurseur).y -= ((*rectangleCurseur).y == 350)? - 100 * 4 : 100;
            } else {
              (*rectangleCurseur).y -= ((*rectangleCurseur).y == 350)? - 100 * ((number - ((*rectangleCurseur).x - 500) / 100) / 9) : 100;
            }

					} else if (event.key.keysym.sym == config.down) {

            if (number >= 9 * 5){
              (*rectangleCurseur).y += ((*rectangleCurseur).y == 350 + 4 * 100)? - 100 * 4 : 100;
            } else {
              (*rectangleCurseur).y += ((*rectangleCurseur).y == 350 + 100 * ((number - ((*rectangleCurseur).x - 500) / 100) / 9))? - 100 * ((number - ((*rectangleCurseur).x - 500) / 100) / 9) : 100;
            }

					} else if (event.key.keysym.sym == config.right) {

            if (number >= 9 * 5){
              (*rectangleCurseur).x += ((*rectangleCurseur).x == 600 + 8 * 100)? - 100 * 8:100;
            } else {
              (*rectangleCurseur).x += ((*rectangleCurseur).x == 600 + 8 * 100)? - 100 * 8:100;
            }

					} else if (event.key.keysym.sym == config.left) {

            if (number >= 9 * 5){
              (*rectangleCurseur).x -= ((*rectangleCurseur).x == 600)? - 100 * 8:100;
            } else {
              (*rectangleCurseur).x -= ((*rectangleCurseur).x == 600)? - 100 * 8:100;
            }

					} else if (event.key.keysym.sym == config.validate) {



					}
          if (updatePc(textureCurseur, rectangleCurseur, min, max, surfacePokemon, listPokemon, texturePc, rectanglePc, renderer))
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

int updatePc (SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int min, int max, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer) {

  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;

  if (displayPokemon (surfacePokemon, min, max, listPokemon, renderer))
    return 1;

  if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int managePcPokemon (MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer) {

  SDL_Surface * surfacePokemon = NULL;
  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  SDL_Surface * surfaceCurseur = NULL;
  SDL_Texture * textureCurseur = NULL;
  Pokemon * listPokemon;

  int pc = displayPc (&surfaceCurseur, &textureCurseur, &surfacePokemon, &listPokemon, mysql, font, config, renderer, &surfacePc, &texturePc);
  closePcPokemon (&surfaceCurseur, &textureCurseur, &surfacePokemon, &listPokemon, &surfacePc, &texturePc);

  return pc;
}

void closePcPokemon (SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Surface ** surfacePc, SDL_Texture ** texturePc) {

  free(*listPokemon);
  if (*surfacePokemon != NULL)
    SDL_FreeSurface(*surfacePokemon);
  if (*surfaceCurseur != NULL)
    SDL_FreeSurface(*surfaceCurseur);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);
  if (*surfacePc != NULL)
    SDL_FreeSurface(*surfacePc);
  if (*texturePc != NULL)
    SDL_DestroyTexture(*texturePc);
}
