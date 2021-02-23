#include "changeName.h"

int displayChangeName (MYSQL * mysql, Pokemon * player, SDL_Surface ** surfaceText, SDL_Texture ** textureText, SDL_Surface ** surfaceWrite, SDL_Texture ** textureWrite, TTF_Font ** font, SDL_Renderer ** renderer) {

  SDL_Rect rectWrite;

  if (loadBMP("../img/background.bmp", surfaceWrite))
    return 1;

  if (displayAll(textureWrite, surfaceWrite, &rectWrite, renderer, 0, 0, 1600, 900))
    return 1;

  SDL_RenderPresent(*renderer);

  return manageEventChangeName(mysql, player, textureWrite, &rectWrite, surfaceText, textureText, font, renderer);
}

int manageEventChangeName (MYSQL * mysql, Pokemon * player, SDL_Texture ** textureWrite, SDL_Rect * rectWrite, SDL_Surface ** surfaceText, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer) {

  SDL_bool programLaunched = SDL_TRUE;
  char newName[32];
  int i = 0;
  int lshift = 0;
  int rshift = 0;

  memset(newName, 0, 32);

  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

          if (event.key.keysym.sym == 27) {

            programLaunched = SDL_FALSE;

          } else if (i != 32 && event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122) {

            newName[i] = event.key.keysym.sym;
            if (lshift || rshift)
              newName[i] -= 32;
            i++;

          } else if (i != 32 && event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57 && (lshift || rshift)) {

            newName[i] = event.key.keysym.sym;
            i++;

          } else if (event.key.keysym.sym == SDLK_RSHIFT) {

            rshift = 1;

          } else if (event.key.keysym.sym == SDLK_LSHIFT) {

            lshift = 1;

          } else if (event.key.keysym.sym == SDLK_RETURN) {

            return saveChange(mysql, player, newName);

          }

          if (updateChangeName(newName, textureWrite, rectWrite, surfaceText, textureText, font, renderer))
            return 1;
          break;

        case SDL_KEYUP:

          if (event.key.keysym.sym == SDLK_RSHIFT) {

            rshift = 0;

          } else if (event.key.keysym.sym == SDLK_LSHIFT) {

            lshift = 0;

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

int saveChange (MYSQL * mysql, Pokemon * player, char newName[32]) {

  char * request;

  request = malloc(strlen("UPDATE POKEBALL SET NamePerso=\"\" WHERE ID=") + strlen(newName) + strlen((*player).id) + 1);
  sprintf(request, "UPDATE POKEBALL SET NamePerso=\"%s\" WHERE ID=%s", newName, (*player).id);

  if (mysql_query(mysql, request)) {
    free (request);
    MySQL_PrintError("error", *mysql);
    return 1;
  }
  free (request);

  strcpy((*player).namePerso, newName);

  return 0;
}

int updateChangeName (char newName[32], SDL_Texture ** textureWrite, SDL_Rect * rectWrite, SDL_Surface ** surfaceText, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer) {

  if (updateRenderer(textureWrite, renderer, rectWrite))
    return 1;

  if (displayText(newName, surfaceText, textureText, font, renderer))
    return 1;

  SDL_RenderPresent(*renderer);

  return 0;
}

int displayText (char newName[32], SDL_Surface ** surfaceText, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer) {

	SDL_Rect rectangle;
  SDL_Color black = {0, 0, 0};

  *surfaceText = TTF_RenderText_Blended(*font, newName, black);

  if (*surfaceText != NULL) {
    if (displayAll(textureText, surfaceText, &rectangle, renderer, 100, 100, -1, -1))
  		return 1;
  }

  return 0;
}

int manageChangeName (MYSQL * mysql, Pokemon * player, TTF_Font ** font, SDL_Renderer ** renderer) {

  SDL_Surface * surfaceText = NULL;
  SDL_Texture * textureText = NULL;
  SDL_Surface * surfaceWrite = NULL;
  SDL_Texture * textureWrite = NULL;

  int changeName = displayChangeName(mysql, player, &surfaceText, &textureText, &surfaceWrite, &textureWrite, font, renderer);
  closeChangeName(&surfaceText, &textureText, &surfaceWrite, &textureWrite);

  return changeName;
}

void closeChangeName (SDL_Surface ** surfaceText, SDL_Texture ** textureText, SDL_Surface ** surfaceWrite, SDL_Texture ** textureWrite) {
  if (*surfaceText != NULL)
    SDL_FreeSurface(*surfaceText);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);
  if (*surfaceWrite != NULL)
    SDL_FreeSurface(*surfaceWrite);
  if (*textureWrite != NULL)
    SDL_DestroyTexture(*textureWrite);
}
