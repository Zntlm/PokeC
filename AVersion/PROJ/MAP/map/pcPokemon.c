#include "pcPokemon.h"

int displayPc (SDL_Texture ** textureText, SDL_Surface ** text, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc) {

  SDL_Rect rectanglePc;
  SDL_Rect rectangleCurseur;
  int number;

  if (loadBMP("../img/pcActionMenu.bmp", surfacePc))
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

  if (displayStats((*listPokemon)[0], font, renderer, text, textureText))
    return 1;

  SDL_RenderPresent(*renderer);

  return managePc(text, textureText, font, mysql, textureCurseurMenu, surfaceCurseurMenu, textureMenu, surfaceMenu, textureCurseur, &rectangleCurseur, number, surfacePokemon, listPokemon, config, texturePc, &rectanglePc, renderer);
}

int displayStats (Pokemon pokemon, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** text, SDL_Texture ** textureText) {

  char * request;
	SDL_Rect rectangle;
  SDL_Color black = {0, 0, 0};

	request = malloc(strlen("NAME : \n") + strlen(pokemon.name) + 1);
	sprintf(request, "NAME : %s\n", pokemon.name);

	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 100, 100, -1, -1))
		return 1;

  request = malloc(strlen("LVL : \n") + sizeof(int) + 1);
	sprintf(request, "LVL : %d\n", pokemon.lvl);

	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 100, 150, -1, -1))
		return 1;

  request = malloc(strlen("PV : \n") + sizeof(int) + 1);
	sprintf(request, "PV : %d\n", pokemon.pv);

	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 100, 200, -1, -1))
		return 1;

  request = malloc(strlen("Attack : \n") + sizeof(int) + 1);
	sprintf(request, "Attack : %d\n", pokemon.attack);

	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 100, 250, -1, -1))
		return 1;

  request = malloc(strlen("Defense : \n") + sizeof(int) + 1);
	sprintf(request, "Defense : %d\n", pokemon.defense);

	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 100, 300, -1, -1))
		return 1;

  request = malloc(strlen("Speed : \n") + sizeof(int) + 1);
	sprintf(request, "Speed : %d\n", pokemon.speed);

	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 100, 350, -1, -1))
		return 1;

  return 0;
}

int selectPokemon (int * number, MYSQL * mysql, Pokemon ** listPokemon) {

  MYSQL_ROW row;
	MYSQL_RES * result;
  MYSQL_ROW rowStats;
	MYSQL_RES * resultStats;
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

    request = malloc(strlen("SELECT PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"\"") + strlen((*listPokemon)[i].name) + 1);
		sprintf(request, "SELECT PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"%s\"", (*listPokemon)[i].name);

    if (mysql_query(mysql, request)){
        free(request);
        MySQL_PrintError("Error query", *mysql);
        return 1;
    }
    free(request);

    resultStats = mysql_store_result(mysql);
    if (resultStats == NULL) {
      MySQL_PrintError("Error extract résult", *mysql);
      return 1;
    }

    rowStats = mysql_fetch_row(resultStats);
    if (rowStats == NULL)
			return 1;

		(*listPokemon)[i].pv = atoi(rowStats[0]) * (*listPokemon)[i].lvl;
		(*listPokemon)[i].attack = atoi(rowStats[1]) * (*listPokemon)[i].lvl;
		(*listPokemon)[i].defense = atoi(rowStats[2]) * (*listPokemon)[i].lvl;
		(*listPokemon)[i].speed = atoi(rowStats[3]) * (*listPokemon)[i].lvl;
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

int managePc (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, MYSQL * mysql, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int number, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, Config config, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer) {

  SDL_bool programLaunched = SDL_TRUE;
  int min = 0;
  int max = (number > 9*5)? 9*5 : number;
  int tmp;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

            if (min == 0 || (*rectangleCurseur).y != 350) {
              (*rectangleCurseur).y -= ((*rectangleCurseur).y == 350)? - 100 * 4 : 100;
            } else {
              min -= 9;
              max -= (max == number)? (max % 9): 9;
            }

					} else if (event.key.keysym.sym == config.down) {

            if (max == number || (*rectangleCurseur).y != 750) {
              (*rectangleCurseur).y += ((*rectangleCurseur).y == 350 + 100 * (((number - min) - ((*rectangleCurseur).x - 500) / 100) / 9))? - 100 * (((number - min) - ((*rectangleCurseur).x - 500) / 100) / 9) : 100;
            } else {
              min += 9;
              max += (max + 9 <= number) ? 9 : number - max;
            }

					} else if (event.key.keysym.sym == config.right) {

            tmp = ((number - min) - ((((*rectangleCurseur).y - 350) / 100) * 9) - 1 > 8)? 8 : (number - min) - ((((*rectangleCurseur).y - 350) / 100) * 9) - 1;
            (*rectangleCurseur).x += ((*rectangleCurseur).x == 600 + tmp * 100)? - 100 * tmp:100;

					} else if (event.key.keysym.sym == config.left) {

            tmp = ((number - min) - ((((*rectangleCurseur).y - 350) / 100) * 9) - 1 > 8)? 8 : (number - min) - ((((*rectangleCurseur).y - 350) / 100) * 9) - 1;
            (*rectangleCurseur).x -= ((*rectangleCurseur).x == 600)? - 100 * tmp:100;

					} else if (event.key.keysym.sym == config.validate) {

            if (displayChoseAction (font, mysql, &((*listPokemon)[min + ((((*rectangleCurseur).y - 350) / 100) * 9) + (((*rectangleCurseur).x - 600) / 100)]), config, textureCurseurMenu, surfaceCurseurMenu, textureMenu, surfaceMenu, renderer))
              return 1;

					}
          if (updatePc((*listPokemon)[min + ((((*rectangleCurseur).y - 350) / 100) * 9) + (((*rectangleCurseur).x - 600) / 100)], font, text, textureText, textureCurseur, rectangleCurseur, min, max, surfacePokemon, listPokemon, texturePc, rectanglePc, renderer))
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

int displayChoseAction (TTF_Font ** font, MYSQL * mysql, Pokemon * selected, Config config, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Renderer ** renderer) {

  SDL_Rect rectangleMenu;
  SDL_Rect rectangleCurseurMenu;

  if (loadBMP("../img/choseActionPc.bmp", surfaceMenu))
    return 1;

  if (displayAll(textureMenu, surfaceMenu, &rectangleMenu, renderer, 50, 500, 500, 300))
    return 1;

  if (loadBMP("../img/curseur.bmp", surfaceCurseurMenu))
    return 1;

  if (displayAll(textureCurseurMenu, surfaceCurseurMenu, &rectangleCurseurMenu, renderer, 100, 600, 25, 25))
    return 1;

  SDL_RenderPresent(*renderer);

  return managePcMenu(font, mysql, selected, config, textureMenu, &rectangleMenu, textureCurseurMenu, &rectangleCurseurMenu, renderer);
}

int managePcMenu (TTF_Font ** font, MYSQL * mysql, Pokemon * selected, Config config, SDL_Texture ** textureMenu, SDL_Rect * rectangleMenu, SDL_Texture ** textureCurseurMenu, SDL_Rect * rectangleCurseurMenu, SDL_Renderer ** renderer) {

  SDL_bool programLaunched = SDL_TRUE;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

            (*rectangleCurseurMenu).y -= ((*rectangleCurseurMenu).y == 600)?-100:100;

					} else if (event.key.keysym.sym == config.down) {

            (*rectangleCurseurMenu).y += ((*rectangleCurseurMenu).y == 700)?-100:100;

					} else if (event.key.keysym.sym == config.validate) {

            if ((*rectangleCurseurMenu).y == 600) {

            } else if ((*rectangleCurseurMenu).y == 700) {
              manageChangePokemon (selected, font, config, renderer, mysql);
              return 0;
            }

					}
          if (updatePcMenu(textureMenu, rectangleMenu, textureCurseurMenu, rectangleCurseurMenu, renderer))
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

int displayChangePokemon (Pokemon * selected, TTF_Font ** font, Config config, SDL_Renderer ** renderer, MYSQL * mysql, Pokemon tab[6]) {

  int tmp;

  if (takePokemonUser(mysql, tab))
    return 1;

  tmp = manageSwitchPokemon (config, font, tab, renderer);
  if (tmp == 1 || tmp == 0)
    return tmp;

  changePokemon(mysql, tab[tmp % 10], selected);

  return 0;
}

int changePokemon (MYSQL * mysql, Pokemon sac, Pokemon * selected) {

  char * request;

  request = malloc(strlen("UPDATE POKEBALL SET PC=1 WHERE ID=") + strlen(sac.id) + 1);
  sprintf(request, "UPDATE POKEBALL SET PC=1 WHERE ID=%s", sac.id);

  if (mysql_query(mysql, request)){
      free(request);
      MySQL_PrintError("Error query", *mysql);
      return 1;
  }
  free(request);

  request = malloc(strlen("UPDATE POKEBALL SET PC=0 WHERE ID=") + strlen((*selected).id) + 1);
  sprintf(request, "UPDATE POKEBALL SET PC=0 WHERE ID=%s", (*selected).id);

  if (mysql_query(mysql, request)){
      free(request);
      MySQL_PrintError("Error query", *mysql);
      return 1;
  }
  free(request);

  strcpy((*selected).id, sac.id);
  (*selected).lvl = sac.lvl;
  (*selected).xp = sac.xp;
  strcpy((*selected).name, sac.name);
  (*selected).img = NULL;

  return 0;
}

int manageChangePokemon (Pokemon * selected, TTF_Font ** font, Config config, SDL_Renderer ** renderer, MYSQL * mysql) {

  Pokemon tab[6];

  for (int i = 0; i < 6; i++) {
		tab[i].img = NULL;
	}

  int change = displayChangePokemon(selected, font, config, renderer, mysql, tab);

  for (int i = 0; i < 6; i++) {
    if (tab[i].img != NULL){
      SDL_DestroyTexture(tab[i].img);
    }
  }

  return change;
}

int updatePcMenu (SDL_Texture ** textureMenu, SDL_Rect * rectangleMenu, SDL_Texture ** textureCurseurMenu, SDL_Rect * rectangleCurseurMenu, SDL_Renderer ** renderer) {

  if (updateRenderer(textureMenu, renderer, rectangleMenu))
    return 1;

  if (updateRenderer(textureCurseurMenu, renderer, rectangleCurseurMenu))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int updatePc (Pokemon pokemon, TTF_Font ** font, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, int min, int max, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Renderer ** renderer) {

  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;

  if (displayPokemon (surfacePokemon, min, max, listPokemon, renderer))
    return 1;

  if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
    return 1;

  if (displayStats(pokemon, font, renderer, text, textureText))
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
  SDL_Surface * surfaceCurseurMenu = NULL;
  SDL_Texture * textureCurseurMenu = NULL;
  SDL_Surface * surfaceMenu = NULL;
  SDL_Texture * textureMenu = NULL;
  SDL_Surface * text = NULL;
  SDL_Texture * textureText = NULL;
  Pokemon * listPokemon;

  int pc = displayPc (&textureText, &text, &textureCurseurMenu, &surfaceCurseurMenu, &textureMenu, &surfaceMenu, &surfaceCurseur, &textureCurseur, &surfacePokemon, &listPokemon, mysql, font, config, renderer, &surfacePc, &texturePc);
  closePcPokemon (&textureText, &text, &textureCurseurMenu, &surfaceCurseurMenu, &textureMenu, &surfaceMenu, &surfaceCurseur, &textureCurseur, &surfacePokemon, &listPokemon, &surfacePc, &texturePc);

  return pc;
}

void closePcPokemon (SDL_Texture ** textureText, SDL_Surface ** text, SDL_Texture ** textureCurseurMenu, SDL_Surface ** surfaceCurseurMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** surfacePokemon, Pokemon ** listPokemon, SDL_Surface ** surfacePc, SDL_Texture ** texturePc) {

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
  if (*surfaceCurseurMenu != NULL)
    SDL_FreeSurface(*surfaceCurseurMenu);
  if (*textureCurseurMenu != NULL)
    SDL_DestroyTexture(*textureCurseurMenu);
  if (*surfaceMenu != NULL)
    SDL_FreeSurface(*surfaceMenu);
  if (*textureMenu != NULL)
    SDL_DestroyTexture(*textureMenu);
  if (*text != NULL)
    SDL_FreeSurface(*text);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);
}
