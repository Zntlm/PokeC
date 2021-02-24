#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "types.h"
#include "manage.h"

int configKey (Config * config, SDL_Renderer ** renderer);
int defineKey (Config * config, SDL_Texture ** texture, SDL_Surface ** page, SDL_Renderer ** renderer);
int pressedKey ();
int manageDefineKey (Config * config, SDL_Renderer ** renderer);
void closeDefineKey (SDL_Texture ** texture, SDL_Surface ** page);

#endif
