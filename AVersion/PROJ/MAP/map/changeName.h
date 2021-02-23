#ifndef _PCPOKEMON_H_
#define _PCPOKEMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"

int displayChangeName (MYSQL * mysql, Pokemon * player, SDL_Surface ** surfaceText, SDL_Texture ** textureText, SDL_Surface ** surfaceWrite, SDL_Texture ** textureWrite, TTF_Font ** font, SDL_Renderer ** renderer);
int manageEventChangeName (MYSQL * mysql, Pokemon * player, SDL_Texture ** textureWrite, SDL_Rect * rectWrite, SDL_Surface ** surfaceText, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer);
int saveChange (MYSQL * mysql, Pokemon * player, char newName[32]);
int updateChangeName (char newName[32], SDL_Texture ** textureWrite, SDL_Rect * rectWrite, SDL_Surface ** surfaceText, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer);
int displayText (char newName[32], SDL_Surface ** surfaceText, SDL_Texture ** textureText, TTF_Font ** font, SDL_Renderer ** renderer);
int manageChangeName (MYSQL * mysql, Pokemon * player, TTF_Font ** font, SDL_Renderer ** renderer);
void closeChangeName (SDL_Surface ** surfaceText, SDL_Texture ** textureText, SDL_Surface ** surfaceWrite, SDL_Texture ** textureWrite);

#endif
