#include "pc.h"

int pcDisplay(int retrun, MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseurPc, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion){

  SDL_Rect rectanglePc;
  SDL_Rect rectangleCurseurPc;
  SDL_Rect rectanglePotion;
  SDL_Rect rectangleCurseurPotion;
  int potion = 0;
  int revive = 0;
  int pokeball = 0;

  if (loadDiplayPc (surfacePc, texturePc, renderer, &rectanglePc))
    return 1;

  if (loadDiplayCurseurPc (surfaceCurseurPc, textureCurseurPc, renderer, &rectangleCurseurPc))
    return 1;

  if (selectItem (mysql, &potion, &pokeball, &revive))
    return 1;

  if (displayItem(potion, pokeball, revive, text, textureText, font, renderer))
    return 1;

  SDL_RenderPresent(*renderer);

  return manageEventPc (&potion, &pokeball, &revive, retrun, mysql, text, textureText, font, config, renderer,  surfacePc, texturePc, &rectanglePc, surfaceCurseurPc, textureCurseurPc, &rectangleCurseurPc, texturePotion, textureCurseurPotion, &rectanglePotion, &rectangleCurseurPotion);
}

int selectItem (MYSQL * mysql, int * potion, int * pokeball, int * revive) {

  MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;

  request = malloc(strlen("SELECT Potion, Revive, Pokeball FROM TRAINER WHERE ID=1") + 1);
  strcpy(request, "SELECT Potion, Revive, Pokeball FROM TRAINER WHERE ID=1");

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

  *potion = atoi(row[0]);
  *revive = atoi(row[1]);
  *pokeball = atoi(row[2]);

  return 0;
}

int displayItem (int potion, int pokeball, int revive, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer) {

	SDL_Rect rectangle;
	SDL_Color black = {0, 0, 0};
  char * request;

  request = malloc(strlen("Potion : ") + sizeof(int) + 1);
  sprintf(request, "Potion : %d", potion);

  *text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 700, 362, 400, -1))
		return 1;

  request = malloc(strlen("Revive : ") + sizeof(int) + 1);
  sprintf(request, "Revive : %d", revive);

  *text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 700, 460, 400, -1))
		return 1;

  request = malloc(strlen("Pokeball : ") + sizeof(int) + 1);
  sprintf(request, "Pokeball : %d", pokeball);

  *text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, &rectangle, renderer, 700, 558, 400, -1))
		return 1;

  return 0;
}

int loadDiplayCurseurPc (SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectangleCurseurPc) {

  //CURSEUR
  // load curseur
  if (loadBMP("../img/curseur.bmp", surfaceCurseuPc))
    return 1;

  // create curseur
  if (createTexture(textureCurseurPc, renderer, surfaceCurseuPc))
    return 1;

  // load texture
  if (loadTexture(textureCurseurPc, rectangleCurseurPc))
    return 1;

  (*rectangleCurseurPc).w = 25;
  (*rectangleCurseurPc).h = 25;
  (*rectangleCurseurPc).x = 325;
  (*rectangleCurseurPc).y = 480;

  // display texture
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int loadDiplayPc (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc) {

  if (loadBMP("../img/pcMenu.bmp", surfacePc))
    return 1;

  // create texture
  if (createTexture(texturePc, renderer, surfacePc))
    return 1;

  // load texture
  if (loadTexture(texturePc, rectanglePc))
    return 1;

  (*rectanglePc).w = 950;
  (*rectanglePc).h = 600;
  (*rectanglePc).x = (1500-(*rectanglePc).w)/2;
  (*rectanglePc).y = (800-(*rectanglePc).h)/2;

  // display texture
  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int manageEventPc (int * potion, int * pokeball, int * revive, int retrun, MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Rect * rectangleCurseurPc, SDL_Texture ** texturePotion, SDL_Texture ** textureCurseurPotion, SDL_Rect * rectanglePotion, SDL_Rect * rectangleCurseurPotion) {

  SDL_bool programLaunched = SDL_TRUE;
  //int nextCase;

  // event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          if (event.key.keysym.sym == config.escape) {
            programLaunched = SDL_FALSE; //Close the pc
          } else if (event.key.keysym.sym == config.up) {
            switch ((*rectangleCurseurPc).x){
                case 325:
                    switch((*rectangleCurseurPc).y){
                        case 578:
                        (*rectangleCurseurPc).y-=98;

                    break;
                    }
                break;

                case 625:
                    switch((*rectangleCurseurPc).y){
                            case 578:
                            (*rectangleCurseurPc).y-=98;

                        break;
                            case 480:
                            (*rectangleCurseurPc).y-=98;
                        break;
                        }
                break;
            }
          } else if (event.key.keysym.sym == config.down) {
            switch((*rectangleCurseurPc).x){
                case 325:
                    switch((*rectangleCurseurPc).y){
                            case 480:
                            (*rectangleCurseurPc).y+=98;
                        break;

                    }
                break;

                case 625:
                    switch((*rectangleCurseurPc).y){
                        case 382:
                            (*rectangleCurseurPc).y+=98;
                        break;
                            case 480:
                            (*rectangleCurseurPc).y+=98;
                        break;

                    }
                break;
            }
          } else if (event.key.keysym.sym == config.right) {
            switch((*rectangleCurseurPc).x){
                case 325:
                (*rectangleCurseurPc).x+=300;
                 break;
            }
          } else if (event.key.keysym.sym == config.left) {
            switch((*rectangleCurseurPc).x){

                case 625:
                switch((*rectangleCurseurPc).y){
                        case 578:
                            (*rectangleCurseurPc).x-=300;
                        break;
                            case 480:
                            (*rectangleCurseurPc).x-=300;
                        break;

                    }
                break;
            }
          } else if (event.key.keysym.sym == config.validate) {
            switch ((*rectangleCurseurPc).x){
                case 625:
                  switch ((*rectangleCurseurPc).y){
                    case 382:
                      if (retrun){
                        if (*potion == 0)
                          return 0;
                        return 11;
                      }
                      if (manageBuy (mysql, font, "../img/pcPotion.bmp", config, renderer))
                        return 1;
                      if (selectItem (mysql, potion, pokeball, revive))
                        return 1;
                    break;

                    case 480:
                      if (retrun){
                        if (*revive == 0)
                          return 0;
                        return 12;
                      }
                      if (manageBuy (mysql, font, "../img/pcRappel.bmp", config, renderer))
                        return 1;
                      if (selectItem (mysql, potion, pokeball, revive))
                        return 1;
                    break;

                    case 578:
                      if (retrun){
                        if (*pokeball == 0)
                          return 0;
                        return 13;
                      }
                      if (manageBuy (mysql, font, "../img/pcPokeball.bmp", config, renderer))
                        return 1;
                      if (selectItem (mysql, potion, pokeball, revive))
                        return 1;
                    break;
                  }
                break;
            }
          }
          if (updateMainPcDisplay (*potion, *pokeball, *revive, mysql, text, textureText, font, texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
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

int updateMainPcDisplay (int potion, int pokeball, int revive, MYSQL * mysql, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Texture ** texturePc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc, SDL_Rect * rectangleCurseurPc) {

  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;
  if (displayItem(potion, pokeball, revive, text, textureText, font, renderer))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int managePcDisplay (int retrun, MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer) {

  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  SDL_Surface * surfaceCurseurPc = NULL;
  SDL_Texture * textureCurseurPc = NULL;
  SDL_Texture * texturePotion = NULL;
  SDL_Texture * textureCurseurPotion = NULL;
  SDL_Surface * text = NULL;
  SDL_Texture * textureText = NULL;


  int pc = pcDisplay(retrun, mysql, &text, &textureText, font, config, renderer, &surfacePc, &texturePc, &surfaceCurseurPc, &textureCurseurPc, &texturePotion, &textureCurseurPotion);

  closePcDisplay(&text, &textureText, &surfacePc, &texturePc, &surfaceCurseurPc, &textureCurseurPc);

  return pc;
}

void closePcDisplay (SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseur) {
  if (*surfacePc != NULL)
    SDL_FreeSurface(*surfacePc);
  if (*texturePc != NULL)
    SDL_DestroyTexture(*texturePc);
  if (*surfaceCurseurPc != NULL)
    SDL_FreeSurface(*surfaceCurseurPc);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);
  if (*text != NULL)
    SDL_FreeSurface(*text);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);
}
