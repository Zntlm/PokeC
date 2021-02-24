#include "menu.h"

// Configuration Menu
int menuDisplay(SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur){

  SDL_Rect rectangleMenu;
  SDL_Rect rectangleCurseur;

  if (loadDiplayMenu (surfaceMenu, textureMenu, renderer, &rectangleMenu))
    return 1;

  if (loadBMP("../img/curseur.bmp", surfaceCurseur))
    return 1;

  if (displayAll(textureCurseur, surfaceCurseur, &rectangleCurseur, renderer, 685, 355, 25, 25))
    return 1;

  if (manageEventMenu (texture, texturePlayer, renderer, rectangle, &rectangleMenu, &rectangleCurseur, rectanglePlayer, textureMenu, textureCurseur))
    return 1;

  return 0;
}

// load and display menu
int loadDiplayMenu (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Renderer ** renderer, SDL_Rect * rectangleMenu) {

  // load home page
  if (loadBMP("../img/menu.bmp", surfaceMenu))
    return 1;

  // create texture
  if (createTexture(textureMenu, renderer, surfaceMenu))
    return 1;

  // load texture
  if (loadTexture(textureMenu, rectangleMenu))
    return 1;

  (*rectangleMenu).w = 250;
  (*rectangleMenu).h = 500;
  (*rectangleMenu).x = (1600-(*rectangleMenu).w)/2;
  (*rectangleMenu).y = (900-(*rectangleMenu).h)/2;

  // display texture
  if (updateRenderer(textureMenu, renderer, rectangleMenu))
    return 1;

  return 0;
}

// manage event for menu display
int manageEventMenu (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Rect * rectanglePlayer, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur) {

  SDL_bool programLaunched = SDL_TRUE;

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_UP://Vers le haut
              if((*rectangleCurseur).y >= 355){
                (*rectangleCurseur).y -= 75;
                if (updateMenuDisplay(texture, texturePlayer, renderer, rectangle, rectanglePlayer, rectangleMenu, rectangleCurseur, textureMenu, textureCurseur))
                  return 1;
              }
              break;

            case SDLK_DOWN://Vers le bas
              if((*rectangleCurseur).y <= 530){
                (*rectangleCurseur).y += 75;
                if (updateMenuDisplay(texture, texturePlayer, renderer, rectangle, rectanglePlayer, rectangleMenu, rectangleCurseur, textureMenu, textureCurseur))
                  return 1;
              }
              break;

            default:
              break;
          }
          break;

        case SDL_KEYUP:
          switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
              programLaunched = SDL_FALSE; //fermer la map
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

// refresh menu
int updateMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer, SDL_Rect * rectangleMenu, SDL_Rect * rectangleCurseur, SDL_Texture ** textureMenu, SDL_Texture ** textureCurseur) {

  SDL_RenderClear(*renderer);

  if (updateRenderer(texture, renderer, rectangle))
    return 1;
  if (updateRenderer(texturePlayer, renderer, rectanglePlayer))
    return 1;
  if (updateRenderer(textureMenu, renderer, rectangleMenu))
    return 1;
  if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
    return 1;

  return 0;
}

// manage error in homeDisplay
int manageMenuDisplay (SDL_Texture ** texture, SDL_Texture ** texturePlayer, SDL_Renderer ** renderer, SDL_Rect * rectangle, SDL_Rect * rectanglePlayer) {

  SDL_Surface * surfaceMenu = NULL;
  SDL_Texture * textureMenu = NULL;
  SDL_Surface * surfaceCurseur = NULL;
  SDL_Texture * textureCurseur = NULL;

  int menu = menuDisplay(texture, texturePlayer, renderer, rectangle, rectanglePlayer, &surfaceMenu, &textureMenu, &surfaceCurseur, &textureCurseur);
  closeMenuDisplay(&surfaceMenu, &textureMenu, &surfaceCurseur, &textureCurseur);

  if (menu)
    return 1;

  return 0;
}

// fre surface and texture used in menu
void closeMenuDisplay (SDL_Surface ** surfaceMenu, SDL_Texture ** textureMenu, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur) {
  if (*surfaceMenu != NULL)
    SDL_FreeSurface(*surfaceMenu);
  if (*textureMenu != NULL)
    SDL_DestroyTexture(*textureMenu);
  if (*surfaceCurseur != NULL)
    SDL_FreeSurface(*surfaceCurseur);
  if (*textureCurseur != NULL)
    SDL_DestroyTexture(*textureCurseur);
}
