#ifndef _TYPES_H_
#define _TYPES_H_

typedef struct Attack {

	char name[100];
	char type[50];
	int Power;
	int Acc;
	int lvl;
	SDL_Texture * text;

} Attack;

typedef struct Pokemon {

	char name[100];
	char type[2][50];
	int pv;
	int pvActuel;
	int attack;
	int defense;
	int speed;
	int lvl;
	char id[256];
	int xp;
	Attack comp[4];
	SDL_Texture * img;

} Pokemon;

typedef struct Config {

	int escape;
	int validate;
	int cancel;
	int up;
	int down;
	int right;
	int left;
	int inventory;

} Config;

#endif
