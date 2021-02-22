#include "mainGame.h"

// matrive map
int matriceMain(int x, int y){

  int MatriceMap[29][50]={
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                          {0, 0, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 3, 2, 3, 3, 3, 1, 1, 1, 1, 3, 0, 0, 0, 0, 5, 5, 5, 0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 3, 3, 3, 0, 0, 3, 3, 3, 1, 3, 3, 3, 5, 5, 5, 5, 5, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                          {0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 1, 1, 1, 3, 5, 5, 5, 5, 5, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
                          {0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 1, 3, 5, 5, 5, 5, 5, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 0, 0, 0, 0, 5, 0},
                          {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 1, 1, 1, 1, 3, 3, 3, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 3, 3, 3, 3, 3, 1, 3, 3, 3, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 3, 3, 3, 3, 3, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 5, 5, 1, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 3, 3, 3, 3, 3, 1, 3, 3, 0, 0, 1, 1, 0, 0, 0, 5, 5, 1, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 3, 3, 3, 3, 1, 0, 3, 0, 0, 0, 4, 4, 1, 5, 5, 5, 1, 5, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4, 1, 0},
                          {0, 5, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 4, 5, 5, 0, 1, 5, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 5, 5, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 0, 0, 0, 0, 1, 1, 1, 0, 0, 5, 1, 1, 1, 1, 2, 4, 0, 0, 1, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 1, 1, 1, 1, 0, 4, 4, 4, 1, 1, 5, 5, 5, 5, 5, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 5, 1, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 5, 1, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 5, 1, 5, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
                          {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 0},
                          {0, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 5, 1, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
                          {0, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 1, 5, 5, 5, 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 1, 5, 5, 5, 5, 1, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 5, 5, 5, 1, 5, 5, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 1, 5, 5, 5, 5, 1, 5, 5, 5, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 5, 5, 5, 1, 5, 5, 5, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
                          {0, 5, 1, 5, 5, 5, 5, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 5, 5, 1, 5, 5, 5, 5, 1, 5, 5, 5, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
                          {0, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0},
                          {0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}
                        };

  return MatriceMap[y/32][x/32];
}

// init display map
int mainGameDisplay (Config config, TTF_Font ** font, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, MYSQL * mysql) {

  SDL_Rect rectangle;
  SDL_Rect rectanglePlayer;

  // load personnage texture
  if (loadBMP("../img/map.bmp", map))
    return 1;

  if (displayAll(texture, map, &rectangle, renderer, 0, 0, -1, -1))
    return 1;

  // load personnage texture
  if (loadBMP("../img/player.bmp", surfacePlayer))
    return 1;

  if (displayAll(texturePlayer, surfacePlayer, &rectanglePlayer, renderer, 32 * 3, 32 * 3, -1, -1))
    return 1;

	SDL_RenderPresent(*renderer);

  if (manageEventMainGame(config, font, renderer, map,  texture, &rectangle, surfacePlayer, texturePlayer, &rectanglePlayer, mysql))
    return 1;

  return 0;
}

// manage event in map
int manageEventMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Surface ** map, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, MYSQL * mysql) {

  SDL_bool programLaunched = SDL_TRUE;
  int nextCase;

  // event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						nextCase = matriceMain((*rectanglePlayer).x, (*rectanglePlayer).y-32);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).y -= 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(mysql, font, config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.down) {

						nextCase = matriceMain((*rectanglePlayer).x, (*rectanglePlayer).y+32);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).y += 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(mysql, font, config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.right) {

						nextCase = matriceMain((*rectanglePlayer).x+32, (*rectanglePlayer).y);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).x += 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(mysql, font, config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.left) {

						nextCase = matriceMain((*rectanglePlayer).x-32, (*rectanglePlayer).y);
						if (nextCase!=0 && nextCase!=6){
							(*rectanglePlayer).x -= 32;
							if (nextCase > 2) {
								if (randomAggro(config, font, renderer, nextCase, mysql))
									return 1;
							}
						}else if(nextCase==6){
							if (manageHomeDisplay(mysql, font, config, renderer, texturePlayer))
								return 1;
						}

					} else if (event.key.keysym.sym == config.inventory) {

						if (manageMenuDisplay (texture, texturePlayer, renderer, rectangle, rectanglePlayer))
							return 1;

					}

					if (updateMainGameDisplay (renderer, texture, rectangle, texturePlayer, rectanglePlayer))
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

// rendom attack by wild pokemon
int randomAggro (Config config, TTF_Font ** font, SDL_Renderer ** renderer, int nextCase, MYSQL * mysql) {

  int numRand;
  Pokemon tab[6];

  srand(time(NULL));
  numRand = rand()%2;

	if (takePokemonUser(mysql, tab))
		return 1;

  if(!numRand) {

    switch (nextCase) {
      case 3:
        if (randomChoseFight (tab, config, font, renderer, mysql, "Roche"))
		return 1;
        break;

      case 4:
        if (randomChoseFight (tab, config, font, renderer, mysql, "Eau"))
		return 1;
        break;

      case 5:
        if (randomChoseFight (tab, config, font, renderer, mysql, "Plante"))
      		return 1;
        break;

      default:
        break;
    }
  }

  return 0;
}

// random chose wild pokemon
int randomChoseFight (Pokemon tab[6], Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, const char * type) {

	int numRow;
	char * request;
	MYSQL_ROW row;
	MYSQL_RES * result;

	request = malloc(strlen("SELECT NamePokemon FROM BELONGSTO WHERE NameType=''") + strlen(type) + 1);
	strcpy(request, "SELECT NamePokemon FROM BELONGSTO WHERE NameType='");
	strcat(request, type);
	strcat(request, "'");

	if (mysql_query(mysql, request)) {
		free (request);
		return 1;
	}

	result = mysql_store_result(mysql);
  if (result == NULL) {
    MySQL_PrintError("Error extract résult", *mysql);
		return 1;
  }

	numRow = rand() % mysql_num_rows(result);

	for (int i = 0; i < numRow+1; i++) {
		row = mysql_fetch_row(result);
	}

	if (managefight(tab, config, font, renderer, mysql, row))
		return 1;

	return 0;
}

// refresh map display
int updateMainGameDisplay (SDL_Renderer ** renderer, SDL_Texture ** texture, SDL_Rect * rectangle, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(texture, renderer, rectangle))
    return 1;

  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;

	SDL_RenderPresent(*renderer);

  return 0;
}

// manage error in homeDisplay
int manageMainGame (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql) {

  SDL_Surface * map = NULL;
  SDL_Surface * surfacePlayer = NULL;
  SDL_Texture * texture = NULL;
  SDL_Texture * texturePlayer = NULL;

  int main = mainGameDisplay(config, font, &surfacePlayer, &texturePlayer, renderer, &map, &texture, mysql);
  closeMainGameDisplay(&map, &texture, &surfacePlayer, &texturePlayer);

  return main;
}

// free surface and texture used in menu
void closeMainGameDisplay (SDL_Surface ** map, SDL_Texture ** texture, SDL_Surface ** surfacePlayer, SDL_Texture ** texturePlayer) {
  if (*map != NULL)
    SDL_FreeSurface(*map);
  if (*texture != NULL)
    SDL_DestroyTexture(*texture);
  if (*surfacePlayer != NULL)
    SDL_FreeSurface(*surfacePlayer);
  if (*texturePlayer != NULL)
    SDL_DestroyTexture(*texturePlayer);
}
