#include "pc.h"


//Configuration Pc
int pcDisplay(SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseurPc){

  SDL_Rect rectanglePc;
  SDL_Rect rectangleCurseurPc;

  if (loadDiplayPc (surfacePc, texturePc, renderer, &rectanglePc))
    return 1;

  if (loadDiplayCurseurPc (surfaceCurseurPc, textureCurseurPc, renderer, &rectangleCurseurPc))
    return 1;

  if (manageEventPc (renderer, surfacePc, texturePc, &rectanglePc, surfaceCurseurPc, textureCurseurPc, &rectangleCurseurPc))
    return 1;

  return 0;
}

// load and display curseur
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
  (*rectangleCurseurPc).x = 685;
  (*rectangleCurseurPc).y = 355;

  // display texture
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;

  return 0;
}

// load and display pc
int loadDiplayPc (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc) {

  // load home page
  if (loadBMP("../img/pcMenu.bmp", surfacePc))
    return 1;

  // create texture
  if (createTexture(texturePc, renderer, surfacePc))
    return 1;

  // load texture
  if (loadTexture(texturePc, rectanglePc))
    return 1;

  (*rectanglePc).w = 250;
  (*rectanglePc).h = 500;
  (*rectanglePc).x = (1600-(*rectanglePc).w)/2;
  (*rectanglePc).y = (900-(*rectanglePc).h)/2;

  // display texture
  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;

  return 0;
}

int manageEventPc (SDL_Renderer ** renderer, SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Rect * rectanglePc, SDL_Surface ** surfaceCurseuPc, SDL_Texture ** textureCurseurPc, SDL_Rect * rectangleCurseurPc) {

  SDL_bool programLaunched = SDL_TRUE;
  int nextCase;

  // event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
              programLaunched = SDL_FALSE; //Close the pc
              break;

            case SDLK_UP://Go Up
              nextCase = MatriceHome((*rectangleCurseurPc).x, (*rectangleCurseurPc).y-65);
              if (nextCase == 1){
                (*rectangleCurseurPc).y -= 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
             /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_DOWN://Go Down
              nextCase = MatriceHome((*rectangleCurseurPc).x, (*rectangleCurseurPc).y+65);
              if (nextCase == 1){
                (*rectangleCurseurPc).y += 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
              /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_RIGHT://To the right
              nextCase = MatriceHome((*rectangleCurseurPc).x+65, (*rectangleCurseurPc).y);
              if (nextCase == 1){
                (*rectangleCurseurPc).x += 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
              /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_LEFT: //The left
              nextCase = MatriceHome((*rectangleCurseurPc).x-65, (*rectangleCurseurPc).y);
              if (nextCase == 1){
                (*rectangleCurseurPc).x -= 65;
                if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                  return 1;
              /* }else if(nextCase==2){

              }else if(nextCase==3){
                   return 0;
                   */
              }
              break;

            case SDLK_SPACE: //Ouvrir menu
              manageMenuDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc);
              if (updateMainPcDisplay (texturePc, textureCurseurPc, renderer, rectanglePc, rectangleCurseurPc))
                return 1;
              break;

            default:
              break;
          }
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

// refresh pc
int updateMainPcDisplay (SDL_Texture ** texturePc, SDL_Texture ** textureCurseurPc, SDL_Renderer ** renderer, SDL_Rect * rectanglePc, SDL_Rect * rectangleCurseurPc) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(texturePc, renderer, rectanglePc))
    return 1;
  if (updateRenderer(textureCurseurPc, renderer, rectangleCurseurPc))
    return 1;

  return 0;
}

// manage error in pcDisplay
int managePcDisplay (SDL_Renderer ** renderer) {

  SDL_Surface * surfacePc = NULL;
  SDL_Texture * texturePc = NULL;
  SDL_Surface * surfaceCurseurPc = NULL;
  SDL_Texture * textureCurseurPc = NULL;

  int pc = pcDisplay(renderer, &surfacePc, &texturePc, &surfaceCurseurPc, &textureCurseurPc);
  closePcDisplay(&surfacePc, &texturePc, &surfaceCurseurPc, &textureCurseurPc);

  if (pc)
    return 1;

  return 0;
}

// free surface and texture used in pcDisplay
void closePcDisplay (SDL_Surface ** surfacePc, SDL_Texture ** texturePc, SDL_Surface ** surfaceCurseurPc, SDL_Texture ** textureCurseur) {
  if (*surfacePc != NULL)
    SDL_FreeSurface(*surfacePc);
  if (*texturePc != NULL)
    SDL_DestroyTexture(*texturePc);
  if (*surfaceCurseurPc != NULL)
    SDL_FreeSurface(*surfaceCurseurPc);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);
}
