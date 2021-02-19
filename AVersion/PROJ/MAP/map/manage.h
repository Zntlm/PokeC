#ifndef _MANAGE_H_
#define _MANAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql/mysql.h>

void SDL_PrintError (const char * message);
void TTF_PrintError(const char * message);
void MySQL_PrintError (const char * message, MYSQL mysql);
void version ();
int connectDataBase (MYSQL * mysql);
int initSDL ();
int createWindow (SDL_Window ** window, int x, int y);
int createRenderer (SDL_Renderer ** renderer, SDL_Window ** window);
int loadBMP (const char * img, SDL_Surface ** surface);
int createTexture (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Surface ** surface);
int loadTexture (SDL_Texture ** texture, SDL_Rect * rectangle);
int updateRenderer (SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle);
int loadFont (TTF_Font ** font);
int displayAll (SDL_Texture ** texture, SDL_Surface ** surface, SDL_Rect * rectangle, SDL_Renderer ** renderer, int x, int y, int w, int h);

#endif
