#include "home.h"

int MatriceHome(int x, int y){
  int matriceHomeInt[12][20]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,0},
    {0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
    {0,1,1,0,0,2,0,2,0,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,0,0,1,1,3,1,1,0,0,1,1,1,1,1,0}
    };
  return matriceHomeInt[(y-90)/60][(x-200)/60];
}

//Display home
int homeDisplay(MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc){

  SDL_Rect rectangleHome;
  SDL_Rect rectanglePlayer;
  SDL_Rect rectanglePc;

  SDL_RenderClear(*renderer);

  // HOME
  // load and display home
  if (loadDiplayHome(renderer, surfaceHome, textureHome, &rectangleHome))

    return 1;

  //PERSONNAGE
  // load and display player in home
  if (displayPlayerHome(renderer, texturePlayer, &rectanglePlayer))
    return 1;

  if (manageEventHomeGame(mysql, font, config, renderer,surfaceHome,textureHome,&rectangleHome,texturePlayer,&rectanglePlayer,texturePc, &rectanglePc))
    return 1;

	SDL_RenderPresent(*renderer);

  return 0;
}

int displayPlayerHome (SDL_Renderer ** renderer, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer) {

  // load texture
  if (loadTexture(texturePlayer, rectanglePlayer))
    return 1;
(*rectanglePlayer).w = 60;
(*rectanglePlayer).h = 60;
(*rectanglePlayer).x = 220+60*9;
(*rectanglePlayer).y = 90+60*11;

  // display texture
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;

	SDL_RenderPresent(*renderer);

  return 0;
}

// load and dipslay home image
int loadDiplayHome (SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome) {

  // load home page
  if (loadBMP("../img/home.bmp", surfaceHome))
    return 1;

  // create texture
  if (createTexture(textureHome, renderer, surfaceHome))
    return 1;

  // load texture
  if (loadTexture(textureHome, rectangleHome))
    return 1;

  (*rectangleHome).w = 1200;
  (*rectangleHome).h = 720;
  (*rectangleHome).x = (1600-(*rectangleHome).w)/2;
  (*rectangleHome).y = (900-(*rectangleHome).h)/2;

  // display texture
  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;

	SDL_RenderPresent(*renderer);

  return 0;
}

int manageEventHomeGame (MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer, SDL_Texture ** texturePc, SDL_Rect * rectanglePc) {

  SDL_bool programLaunched = SDL_TRUE;
  int nextCase;

  // event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          if (event.key.keysym.sym == config.escape) {
            programLaunched = SDL_FALSE; //Close Home
          } else if (event.key.keysym.sym == config.up) {
            nextCase = MatriceHome((*rectanglePlayer).x, (*rectanglePlayer).y-60);
            if (nextCase == 1){
              (*rectanglePlayer).y -= 60;
            }else if(nextCase==2){
                  managePcDisplay(0, mysql, font, config, renderer);
            }else if(nextCase==3){
                 return 0;
            }
          } else if (event.key.keysym.sym == config.down) {
            nextCase = MatriceHome((*rectanglePlayer).x, (*rectanglePlayer).y+60);
            if (nextCase == 1){
              (*rectanglePlayer).y += 60;
            }else if(nextCase==2){
                  managePcDisplay(0, mysql, font, config, renderer);
            }else if(nextCase==3){
                 return 0;
            }
          } else if (event.key.keysym.sym == config.right) {
            nextCase = MatriceHome((*rectanglePlayer).x+60, (*rectanglePlayer).y);
            if (nextCase == 1){
              (*rectanglePlayer).x += 60;
            }else if (nextCase==2){
                  managePcDisplay(0, mysql, font, config, renderer);
            }else if(nextCase==3){
                 return 0;
            }
          } else if (event.key.keysym.sym == config.left) {
            nextCase = MatriceHome((*rectanglePlayer).x-60, (*rectanglePlayer).y);
            if (nextCase == 1){
              (*rectanglePlayer).x -= 60;
            }else if(nextCase==2){
                  managePcDisplay(0, mysql, font, config, renderer);
            }else if(nextCase==3){
                 return 0;
            }
          }
          if (updateMainHomeDisplay (renderer, textureHome, rectangleHome, texturePlayer, rectanglePlayer))
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

//Update Home Display
int updateMainHomeDisplay (SDL_Renderer ** renderer, SDL_Texture ** textureHome, SDL_Rect * rectangleHome, SDL_Texture ** texturePlayer, SDL_Rect * rectanglePlayer) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(textureHome, renderer, rectangleHome))
    return 1;

  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;

	SDL_RenderPresent(*renderer);

  return 0;
}

// manage error in homeDisplay
int manageHomeDisplay (MYSQL * mysql, TTF_Font ** font, Config config, SDL_Renderer ** renderer, SDL_Texture ** texturePlayer) {

  SDL_Surface * surfaceHome = NULL;
  SDL_Texture * textureHome = NULL;
  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  int home = homeDisplay(mysql, font, config, renderer, texturePlayer, &surfaceHome, &textureHome, &surfacePc, &texturePc);

  closeHomeDisplay(&surfaceHome, &textureHome, &surfacePc, &texturePc);

  if (home)
    return 1;

  return 0;
}

// free surface and texture used in homeDisplay
void closeHomeDisplay (SDL_Surface ** surfaceHome, SDL_Texture ** textureHome, SDL_Surface ** surfacePc, SDL_Texture ** texturePc) {
  if (*surfaceHome != NULL)
    SDL_FreeSurface(*surfaceHome);
  if (*textureHome != NULL)
    SDL_DestroyTexture(*textureHome);
 if (*surfacePc != NULL)
    SDL_FreeSurface(*surfacePc);
  if (*texturePc != NULL)
    SDL_DestroyTexture(*texturePc);
}
