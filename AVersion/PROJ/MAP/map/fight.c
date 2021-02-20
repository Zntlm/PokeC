#include "fight.h"

// init fight display
int fightDisplay (Config config, Pokemon tab[6], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, MYSQL * mysql, MYSQL_ROW row, SDL_Renderer ** renderer, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv) {

	Pokemon adv;
	int actu = 0;
	char  * request;
	SDL_Rect rectangleBackground;
	SDL_Rect rectanglePokemonPlayer;
	SDL_Rect rectanglePokemonAdv;
	SDL_Rect rectangleChoseActionFight;
	SDL_Rect rectangleCurseur;
	SDL_Rect rectangle;
	SDL_Color black = {0, 0, 0};

	if (takePokemonUser(mysql, tab))
		return 1;

	if (takePokemonAdv(mysql, &adv, tab[0].lvl, row))
		return 1;

	if (loadBMP("../img/background.bmp", surfaceBackground))
		return 1;

	if (displayAll(textureBackground, surfaceBackground, &rectangleBackground, renderer, 0, 0, -1, -1))
		return 1;

	if (loadDiplayPokemonAdv(surfacePokemonAdv, texturePokemonAdv, renderer, &rectanglePokemonAdv, row))
		return 1;

	if (loadDiplayPokemonPlayer(mysql, surfacePokemonPlayer, texturePokemonPlayer, renderer, &rectanglePokemonPlayer, &(tab[actu])))
		return 1;

	if (displayPvPokemon (text, textureText, font, black, tab[actu], 100, 0, renderer, &rectangle))
		return 1;

	if (displayPvPokemon (text, textureText, font, black, adv, 1100, 0, renderer, &rectangle))
		return 1;

	if (displayChoseActionFight(surfaceChoseActionFight, textureChoseActionFight, &rectangleChoseActionFight, surfaceCurseur, textureCurseur, &rectangleCurseur, renderer))
		return 1;

	SDL_RenderPresent(*renderer);

	if (manageEventChoseActionFight (config, surfacePokemonPlayer, &actu, &rectanglePokemonPlayer, &rectanglePokemonAdv, &rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText, &adv, mysql, text, font, black, surfaceChoseAttack, textureChoseAttack, tab, surfaceSelect, textureSelect, textureChoseActionFight, &rectangleChoseActionFight, textureCurseur, &rectangleCurseur, renderer))
		return 1;

	return 0;
}

// refresh fight display
int updateFightDisplay (SDL_Surface ** surfacePokemonPlayer, MYSQL * mysql, Pokemon * player, Pokemon adv, SDL_Surface ** text, TTF_Font ** font, SDL_Renderer ** renderer, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText) {

	SDL_Color black = {0, 0, 0};
	SDL_Rect rectangle;
	int tmp;

	if (updateRenderer(textureBackground, renderer, rectangleBackground))
		return 1;

	if (updateRenderer(texturePokemonAdv, renderer, rectanglePokemonAdv))
		return 1;

	if ((*player).img != NULL) {
		if (updateRenderer(&((*player).img), renderer, rectanglePokemonPlayer))
			return 1;
	} else {
		if (loadDiplayPokemonPlayer(mysql, surfacePokemonPlayer, &((*player).img), renderer, rectanglePokemonPlayer, player))
			return 1;
	}

	if (displayPvPokemon (text, textureText, font, black, *player, 100, 0, renderer, &rectangle))
		return 1;
	if (displayPvPokemon (text, textureText, font, black, adv, 1100, 0, renderer, &rectangle))
		return 1;

	SDL_RenderPresent(*renderer);

	return 0;
}

// manage event in chose action fight
int manageEventChoseActionFight (Config config, SDL_Surface ** surfacePokemonPlayer, int * actu, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText, Pokemon * adv, MYSQL * mysql, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, Pokemon pokemonPlayer[6], SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer) {

	int curseur = 0;
	int action = 0;
	int tmp = 0;
	int pvOld = 0;
	int i = 0;
	char poss = 0;
	SDL_bool programLaunched = SDL_TRUE;
	// event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						poss += (poss - 2 < 0)?2:-2;

					} else if (event.key.keysym.sym == config.down) {

						poss += (poss + 2 > 3)?-2:2;

					} else if (event.key.keysym.sym == config.right) {

						poss += (poss + 1 > 3)?-3:1;

					} else if (event.key.keysym.sym == config.left) {

						poss += (poss - 1 < 0)?3:-1;

					} else if (event.key.keysym.sym == config.validate) {

						switch (poss) {
							case 0: // fight
								action = 1;
								if (manageChoseAtack (config, surfacePokemonPlayer, *actu, rectanglePokemonPlayer, rectanglePokemonAdv, rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText, adv, mysql, text, font, black, surfaceChoseAttack, textureChoseAttack, pokemonPlayer, textureCurseur, rectangleCurseur, renderer))
									return 1;
								if ((*adv).pvActuel <= 0)
									return finishFight(mysql, &(pokemonPlayer[*actu]), (*adv).lvl);
								break;

							case 1: // pokemon
								do {
									tmp = manageSwitchPokemon (config, font, pokemonPlayer, renderer);
									if (tmp == 1)
										return 1;
								} while (pokemonPlayer[tmp % 10].pvActuel == 0);

								*actu = tmp % 10;
								action = 1;

								break;

							case 2: // item
								tmp = managePcDisplay(1, mysql, font, config, renderer);
								if (tmp == 1)
									return 1;
								if (tmp == 11){
									tmp = manageSwitchPokemon (config, font, pokemonPlayer, renderer);
									if (pokemonPlayer[tmp % 10].pvActuel != 0 && pokemonPlayer[tmp % 10].pvActuel != pokemonPlayer[tmp % 10].pv) {
										pokemonPlayer[tmp % 10].pvActuel += pokemonPlayer[tmp % 10].pv / 4;
										if (pokemonPlayer[tmp % 10].pvActuel > pokemonPlayer[tmp % 10].pv)
											pokemonPlayer[tmp % 10].pvActuel = pokemonPlayer[tmp % 10].pv;
									}
									if (deleteItem ("Potion", mysql))
										return 1;
								} else if (tmp == 12) {
									tmp = manageSwitchPokemon (config, font, pokemonPlayer, renderer);
									if (pokemonPlayer[tmp % 10].pvActuel == 0) {
										pokemonPlayer[tmp % 10].pvActuel += pokemonPlayer[tmp % 10].pv / 2;
									}
									if (deleteItem ("Revive", mysql))
										return 1;
								} else if (tmp == 13) {
									if (rand()%2) {
										if (catchPokemon(adv, mysql))
											return 1;
									}
									if (deleteItem ("Pokeball", mysql))
										return 1;
									return 0;
								}
								action = 1;
								break;

							case 3: // run
								return 0;
								break;
						}
					}

					if (action == 1){
						pvOld = pokemonPlayer[*actu].pvActuel;
						if (actionAttack (mysql, (*adv).lvl, (*adv).attack, (*adv).comp[rand()%4], &(pokemonPlayer[*actu])))
							return 1;

						tmp = pokemonPlayer[*actu].pvActuel;
						pokemonPlayer[*actu].pvActuel = pvOld;

						while (tmp != pokemonPlayer[*actu].pvActuel) {
							if (updateFightDisplay (surfacePokemonPlayer, mysql, &(pokemonPlayer[*actu]), *adv, text, font, renderer, rectanglePokemonPlayer, rectanglePokemonAdv, rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText))
								return 1;
							pokemonPlayer[*actu].pvActuel -= 1;
							SDL_Delay(1000/60);
						}
					}

					for (i = 0; i < 6 && pokemonPlayer[i].pvActuel <= 0; i++);
					if (i == 6)
						return 0;

					if (pokemonPlayer[*actu].pvActuel == 0) {
						do {
							tmp = manageSwitchPokemon (config, font, pokemonPlayer, renderer);
							if (tmp == 1)
								return 1;
						} while (pokemonPlayer[tmp % 10].pvActuel == 0);
						*actu = tmp % 10;
					}

					if (updateFightDisplay (surfacePokemonPlayer, mysql, &(pokemonPlayer[*actu]), *adv, text, font, renderer, rectanglePokemonPlayer, rectanglePokemonAdv, rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText))
						return 1;

					action = 0;
					if (updateDisplayChoseActionFight (textureChoseActionFight, rectangleChoseActionFight, textureCurseur, rectangleCurseur, poss, renderer))
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

int deleteItem (const char * item, MYSQL * mysql) {

	MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;

	request = malloc(strlen("SELECT  FROM TRAINER WHERE ID=1") + strlen(item) + 1);
  sprintf(request, "SELECT %s FROM TRAINER WHERE ID=1", item);

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

  request = malloc(strlen("UPDATE TRAINER SET = WHERE ID=1") + strlen(item) + sizeof(int) + 1);
  sprintf(request, "UPDATE TRAINER SET %s=%d WHERE ID=1", item, atoi(row[0]) - 1);

  if (mysql_query(mysql, request)){
      free(request);
      MySQL_PrintError("Error query", *mysql);
      return 1;
  }
  free(request);

	return 0;
}

int catchPokemon (Pokemon * adv, MYSQL * mysql) {

	MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;

	request = malloc(strlen("SELECT MAX(ID) FROM POKEBALL") + 1);
  strcpy(request, "SELECT MAX(ID) FROM POKEBALL");

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

	request = malloc(strlen("INSERT INTO POKEBALL (ID, LVL, XP, IDTrainer, NamePokemon, PC) VALUE (, , 0, 1, \"\", 1)") + strlen((*adv).name) + sizeof(int) * 2 + 1);
  sprintf(request, "INSERT INTO POKEBALL (ID, LVL, XP, IDTrainer, NamePokemon, PC) VALUE (%d, %d, 0, 1, \"%s\", 1)", atoi(row[0]) + 1, (*adv).lvl, (*adv).name);

  if (mysql_query(mysql, request)){
      free(request);
      MySQL_PrintError("Error query", *mysql);
      return 1;
  }
  free(request);

	return 0;
}

// player win fight
int finishFight (MYSQL * mysql, Pokemon * pokemonPlayer, int lvlAdv) {

	char * request;
	MYSQL_ROW row;
	MYSQL_RES * result;

	(*pokemonPlayer).xp += lvlAdv;

	while ((*pokemonPlayer).xp > (*pokemonPlayer).lvl)
		(*pokemonPlayer).xp -= ++(*pokemonPlayer).lvl;

	request = malloc(strlen("UPDATE POKEBALL SET LVL= ,XP= WHERE ID=") + strlen((*pokemonPlayer).id) + sizeof(int) * 2 + 1);
	sprintf(request, "UPDATE POKEBALL SET LVL=%d ,XP=%d WHERE ID=%s", (*pokemonPlayer).lvl, (*pokemonPlayer).xp, (*pokemonPlayer).id);

	if (mysql_query(mysql, request)){
		free(request);
    MySQL_PrintError("Error query", *mysql);
    return 1;
	}
	free(request);

	request = malloc(strlen("SELECT PokeDollar FROM TRAINER WHERE ID=1") + 1);
  sprintf(request, "SELECT PokeDollar FROM TRAINER WHERE ID=1");

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

	request = malloc(strlen("UPDATE TRAINER SET PokeDollar= WHERE ID=1") + sizeof(int) + 1);
  sprintf(request, "UPDATE TRAINER SET PokeDollar=%d WHERE ID=1", atoi(row[0]) + lvlAdv * 100);

  if (mysql_query(mysql, request)){
      free(request);
      MySQL_PrintError("Error query", *mysql);
      return 1;
  }
  free(request);

	return 0;
}

// mange event in attack menu
int manageChoseAtack (Config config, SDL_Surface ** surfacePokemonPlayer, int actu, SDL_Rect * rectanglePokemonPlayer, SDL_Rect * rectanglePokemonAdv, SDL_Rect * rectangleBackground, SDL_Texture ** textureBackground, SDL_Texture ** texturePokemonAdv, SDL_Texture ** texturePokemonPlayer, SDL_Texture ** textureText, Pokemon * adv, MYSQL * mysql, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, Pokemon pokemonPlayer[6], SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer) {

	SDL_bool programLaunched = SDL_TRUE;
	SDL_Rect rectangleChoseAttack;
	SDL_Rect rectangleAttack[4];
	SDL_Rect rectangle;
	int tmp;
	int pvOld;

	(*rectangleCurseur).x = 475;
	(*rectangleCurseur).y = 575;

	if (displayChoseAttack (&rectangleChoseAttack, rectangleCurseur, textureCurseur, rectangleAttack, surfaceChoseAttack, textureChoseAttack, text, font, black, &(pokemonPlayer[actu]), renderer))
		return 1;

	// event
  while (programLaunched) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {

        case SDL_KEYDOWN:

					if (event.key.keysym.sym == config.escape) {

						programLaunched = SDL_FALSE;

					} else if (event.key.keysym.sym == config.up) {

						(*rectangleCurseur).y -= ((*rectangleCurseur).y == 575) ? - (3 * 75) : 75;

					} else if (event.key.keysym.sym == config.down) {

						(*rectangleCurseur).y += ((*rectangleCurseur).y == 575 + 3 * 75) ? - (3 * 75) : 75;

					} else if (event.key.keysym.sym == config.validate) {

						pvOld = (*adv).pvActuel;
						if (actionAttack(mysql, (pokemonPlayer[actu]).lvl, (pokemonPlayer[actu]).attack, (pokemonPlayer[actu]).comp[((*rectangleCurseur).y - 575) / 75], adv))
							return 1;

						tmp = (*adv).pvActuel;
						(*adv).pvActuel = pvOld;

						while (tmp != (*adv).pvActuel) {
							if (updateFightDisplay (surfacePokemonPlayer, mysql, &(pokemonPlayer[actu]), *adv, text, font, renderer, rectanglePokemonPlayer, rectanglePokemonAdv, rectangleBackground, textureBackground, texturePokemonAdv, texturePokemonPlayer, textureText))
								return 1;
							(*adv).pvActuel -= 1;
							SDL_Delay(1000/60);
						}

						return 0;

					}
	  			if (updateDisplayAtack (&rectangleChoseAttack, rectangleCurseur, rectangleAttack, textureCurseur, textureChoseAttack, &(pokemonPlayer[actu]), renderer))
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

// use attack
int actionAttack (MYSQL * mysql, int lvl, int attack, Attack selected, Pokemon * adv) {

	int numRand;
	MYSQL_ROW row;
	MYSQL_RES * result;
	char * request;
	int power = selected.Power * lvl;

	if (attack < (*adv).defense) {
		power /= 2;
	}

	numRand = rand()%100;

	if (selected.Acc < numRand) {
		return 0;
	}

	for (int i = 0; i < 2; i++) {
		request = malloc(strlen("SELECT Value FROM AMPLIFICATOR WHERE NameAttack=\"\" AND NameDefense=\"\"") + strlen(selected.type) + strlen((*adv).type[i]) + 1);

		sprintf(request, "SELECT Value FROM AMPLIFICATOR WHERE NameAttack=\"%s\" AND NameDefense=\"%s\"", selected.type, (*adv).type[i]);

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
			continue;

		if (!strcmp("0.5", row[0])){
			power /= 2;
		} else if (!strcmp("2", row[0])) {
			power *= 2;
		}
	}

	(*adv).pvActuel -= power;
	if ((*adv).pvActuel < 0)
		(*adv).pvActuel = 0;

	return 0;
}

// display attacks
int displayChoseAttack (SDL_Rect * rectangleChoseAttack, SDL_Rect * rectangleCurseur, SDL_Texture ** textureCurseur, SDL_Rect rectangleAttack[4], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** text, TTF_Font ** font, SDL_Color black, Pokemon * pokemonPlayer, SDL_Renderer ** renderer) {

	char * request;

	if (loadBMP("../img/attack.bmp", surfaceChoseAttack))
		return 1;

	if (displayAll(textureChoseAttack, surfaceChoseAttack, rectangleChoseAttack, renderer, 400, 500, 800, 400))
		return 1;

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	for (int i = 0; i < 4; i++) {
		request = malloc(strlen((*pokemonPlayer).comp[i].name) + 1);
		strcpy(request, (*pokemonPlayer).comp[i].name);

		*text = TTF_RenderText_Blended(*font, request, black);
		free(request);

		if (displayAll(&(*pokemonPlayer).comp[i].text, text, &(rectangleAttack[i]), renderer, 700, 575 + i * 65, 300, -1))
			return 1;

	}
	SDL_RenderPresent(*renderer);

	return 0;
}

// refresh list of attack
int updateDisplayAtack (SDL_Rect * rectangleChoseAttack, SDL_Rect * rectangleCurseur, SDL_Rect rectangleAttack[4], SDL_Texture ** textureCurseur, SDL_Texture ** textureChoseAttack, Pokemon * pokemonPlayer, SDL_Renderer ** renderer) {

	if (updateRenderer(textureChoseAttack, renderer, rectangleChoseAttack))
		return 1;

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	for (int i = 0; i < 4; i++) {
		if (updateRenderer(&(*pokemonPlayer).comp[i].text, renderer, &(rectangleAttack[i])))
			return 1;
	}
	SDL_RenderPresent(*renderer);

	return 0;
}

// refresh possibles action in fight menu
int updateDisplayChoseActionFight (SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, char poss, SDL_Renderer ** renderer) {

	if (updateRenderer(textureChoseActionFight, renderer, rectangleChoseActionFight))
		return 1;

	switch (poss) {
		case 0:
			(*rectangleCurseur).x = 475;
			(*rectangleCurseur).y = 640;
			break;

		case 1:
			(*rectangleCurseur).x = 875;
			(*rectangleCurseur).y = 640;
			break;

		case 2:
			(*rectangleCurseur).x = 475;
			(*rectangleCurseur).y = 775;
			break;

		case 3:
			(*rectangleCurseur).x = 875;
			(*rectangleCurseur).y = 775;
			break;

		default:
			break;
	}

	if (updateRenderer(textureCurseur, renderer, rectangleCurseur))
		return 1;

	SDL_RenderPresent(*renderer);

	return 0;
}

// displays possibles action in fight
int displayChoseActionFight (SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Rect * rectangleChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Rect * rectangleCurseur, SDL_Renderer ** renderer) {

	if (loadBMP("../img/choseActionFight.bmp", surfaceChoseActionFight))
		return 1;

	if (displayAll(textureChoseActionFight, surfaceChoseActionFight, rectangleChoseActionFight, renderer, 400, 500, 800, 400))
		return 1;

	if (loadBMP("../img/curseur.bmp", surfaceCurseur))
		return 1;

	if (displayAll(textureCurseur, surfaceCurseur, rectangleCurseur, renderer, 475, 640, 50, 50))
		return 1;

	return 0;
}

// display lvl and pv of a pokmeon
int displayPvPokemon (SDL_Surface ** text, SDL_Texture ** textureText, TTF_Font ** font, SDL_Color black, Pokemon pokemonActu, int x, int y, SDL_Renderer ** renderer, SDL_Rect * rectangle) {

	char * request;
	SDL_Rect rectangleText;

	request = malloc(strlen(pokemonActu.name) + sizeof(int) * 3 + strlen(" LVL :  | PV : /") + 1);

	sprintf(request, "%s LVL : %d | PV : %d/%d", pokemonActu.name, pokemonActu.lvl, pokemonActu.pvActuel, pokemonActu.pv);
	*text = TTF_RenderText_Blended(*font, request, black);

	free (request);
	if (displayAll(textureText, text, rectangle, renderer, x, y, 400, -1))
		return 1;

	return 0;
}

// display ia pokemon
int loadDiplayPokemonPlayer (MYSQL * mysql, SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, Pokemon * pokemonActu) {

  char * request;
  int img;
  int i;
  double mul;

  request = malloc(strlen("../img/pokemon/.bmp") + strlen((*pokemonActu).name) + 1);

  strcpy(request, "../img/pokemon/");
  strcat(request, (*pokemonActu).name);
  strcat(request, ".bmp");

  // load home page
  img = loadBMP(request, surface);
  free(request);
  if (img)
    return 1;

  // create texture
  if (createTexture(&((*pokemonActu).img), renderer, surface))
    return 1;

  // load texture
  if (loadTexture(&((*pokemonActu).img), rectangle))
    return 1;

  (*rectangle).x = 200;
  (*rectangle).y = 200;

  if ((*rectangle).w > (*rectangle).h) {
    mul = 200.0/(*rectangle).w;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  } else {
    mul = 200.0/(*rectangle).h;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  }

  // display texture
  if (updateRenderer(&((*pokemonActu).img), renderer, rectangle))
    return 1;

  return 0;
}

// display user pokemon
int loadDiplayPokemonAdv (SDL_Surface ** surface, SDL_Texture ** texture, SDL_Renderer ** renderer, SDL_Rect * rectangle, MYSQL_ROW row) {

  char * request;
  int img;
  double mul;

  request = malloc(strlen("../img/pokemon/.bmp") + strlen(row[0]) + 1);

  strcpy(request, "../img/pokemon/");
  strcat(request, row[0]);
  strcat(request, ".bmp");

  // load home page
  img = loadBMP(request, surface);
  free(request);
  if (img)
    return 1;

  // create texture
  if (createTexture(texture, renderer, surface))
    return 1;

  // load texture
  if (loadTexture(texture, rectangle))
    return 1;

  (*rectangle).x = 1200;
  (*rectangle).y = 200;

  if ((*rectangle).w > (*rectangle).h) {
    mul = 200.0/(*rectangle).w;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  } else {
    mul = 200.0/(*rectangle).h;
    (*rectangle).w *= mul;
    (*rectangle).h *= mul;
  }

  // display texture
  if (updateRenderer(texture, renderer, rectangle))
    return 1;

  return 0;
}

// select user pokemon
int takePokemonUser (MYSQL * mysql, Pokemon * tab) {

	int numRow;
	MYSQL_ROW row;
	MYSQL_RES *result;
	MYSQL_ROW rowPokemon;
	MYSQL_RES *resultPokemon;
	char * request;
	int i;
	int j;

	if (mysql_query(mysql, "SELECT NamePokemon, ID, lvl, XP FROM POKEBALL WHERE IDTrainer=1 AND PC=0 ORDER BY LVL DESC")){
	    MySQL_PrintError("Error query", *mysql);
	    return 1;
	}

	result = mysql_store_result(mysql);
  if (result == NULL) {
    MySQL_PrintError("Error extract résult", *mysql);
		return 1;
  }

	for (i = 0; i < 6; i++){

		row = mysql_fetch_row(result);
		if (row == NULL) {
			strcpy(tab[i].name, "");
			continue;
		}
		strcpy(tab[i].name, row[0]);
		strcpy(tab[i].id, row[1]);
		tab[i].lvl = atoi(row[2]);
		tab[i].xp = atoi(row[3]);

		request = malloc(strlen("SELECT PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"\"") + strlen(tab[i].name) + 1);
		sprintf(request, "SELECT PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"%s\"", tab[i].name);

		if (mysql_query(mysql, request)){
			free(request);
	    MySQL_PrintError("Error query", *mysql);
	    return 1;
		}
		free(request);

		resultPokemon = mysql_store_result(mysql);
	  if (resultPokemon == NULL) {
	    MySQL_PrintError("Error extract résult", *mysql);
			return 1;
	  }

		row = mysql_fetch_row(resultPokemon);
		if (row == NULL)
			return 1;

		tab[i].pv = atoi(row[0]) * tab[i].lvl;
		tab[i].pvActuel = tab[i].pv;
		tab[i].attack = atoi(row[1]) * tab[i].lvl;
		tab[i].defense = atoi(row[2]) * tab[i].lvl;
		tab[i].speed = atoi(row[3]) * tab[i].lvl;

		if (takeComp(mysql, &(tab[i])))
			return 1;

		if (takeTypes(mysql, &(tab[i])))
			return 1;
	}

	return 0;
}

// select ia pokemon
int takePokemonAdv (MYSQL * mysql, Pokemon * adv, int lvlPlayer, MYSQL_ROW row) {

	int numRow;
	char * request;
	MYSQL_RES *result;
	int numRand;

  srand(time(NULL));
  (*adv).lvl = rand()%lvlPlayer + 1;

	request = malloc(strlen("SELECT Name, PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"\"") + strlen(row[0]) + 1);
	strcpy(request, "SELECT Name, PV, Attack, Defense, Speed FROM POKEMON WHERE Name=\"");
	strcat(request, row[0]);
	strcat(request, "\"");

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

	strcpy((*adv).name, row[0]);
	(*adv).pv = atoi(row[1]) * (*adv).lvl;
	(*adv).pvActuel = atoi(row[1]) * (*adv).lvl;
	(*adv).attack = atoi(row[2]) * (*adv).lvl;
	(*adv).defense = atoi(row[3]) * (*adv).lvl;
	(*adv).speed = atoi(row[4]) * (*adv).lvl;

	if (takeComp(mysql, adv))
		return 1;

	if (takeTypes(mysql, adv))
		return 1;

	return 0;
}

// select and store types of a pokemon
int takeTypes (MYSQL * mysql, Pokemon * pokemon) {

	MYSQL_ROW rowType;
	MYSQL_RES *resultType;
	char * requestType;

	requestType = malloc(strlen("SELECT NameType FROM BELONGSTO WHERE NamePokemon=\"\"") + strlen((*pokemon).name) + 1);
	sprintf(requestType, "SELECT NameType FROM BELONGSTO WHERE NamePokemon=\"%s\"", (*pokemon).name);

	if (mysql_query(mysql, requestType)){
			free(requestType);
			MySQL_PrintError("Error query", *mysql);
			return 1;
	}
	free(requestType);

	resultType = mysql_store_result(mysql);
	if (resultType == NULL) {
		MySQL_PrintError("Error extract résult", *mysql);
		return 1;
	}

	for (int j = 0; j < 2; j++) {
		rowType = mysql_fetch_row(resultType);
		if (rowType == NULL) {
			(*pokemon).type[j][0] = 0;
			continue;
		}
		strcpy((*pokemon).type[j], rowType[0]);
	}

	return 0;
}

// select and store the skills of a pokemon
int takeComp (MYSQL * mysql, Pokemon * pokemon) {

	MYSQL_ROW rowLearn;
	MYSQL_RES *resultLearn;
	char * requestLearn;
	MYSQL_ROW rowAttack;
	MYSQL_RES *resultAttack;
	char * requestAttack;

	requestLearn = malloc(sizeof("SELECT * FROM LEARN WHERE NamePokemon=\"\"") + sizeof((*pokemon).name) + 1);

	sprintf(requestLearn, "SELECT * FROM LEARN WHERE NamePokemon=\"%s\"", (*pokemon).name);

	if (mysql_query(mysql, requestLearn)){
			free(requestLearn);
			MySQL_PrintError("Error query", *mysql);
			return 1;
	}
	free(requestLearn);

	resultLearn = mysql_store_result(mysql);
	if (resultLearn == NULL) {
		MySQL_PrintError("Error extract résult", *mysql);
		return 1;
	}

	for (int j = 0; j < 4; j++) {
		rowLearn = mysql_fetch_row(resultLearn);
		if (rowLearn == NULL)
			return 0;

		requestAttack = malloc(strlen("SELECT * FROM ATTACK WHERE Name=\"\"") + strlen(rowLearn[1]) + 1);
		sprintf(requestAttack, "SELECT * FROM ATTACK WHERE Name=\"%s\"", rowLearn[1]);

		if (mysql_query(mysql, requestAttack)){
				free(requestAttack);
				MySQL_PrintError("Error query", *mysql);
				return 1;
		}
		free(requestAttack);

		resultAttack = mysql_store_result(mysql);
		if (resultAttack == NULL) {
			MySQL_PrintError("Error extract résult", *mysql);
			return 1;
		}
		rowAttack = mysql_fetch_row(resultAttack);

		if (rowAttack == NULL)
			continue;

		strcpy((*pokemon).comp[j].name, rowLearn[1]);
		strcpy((*pokemon).comp[j].type, rowAttack[3]);
		(*pokemon).comp[j].lvl = atoi(rowLearn[2]);
		(*pokemon).comp[j].Power = atoi(rowAttack[1]);
		(*pokemon).comp[j].Acc = atoi(rowAttack[2]);
	}

	return 0;
}

// manage error in homeDisplay
int managefight (Config config, TTF_Font ** font, SDL_Renderer ** renderer, MYSQL * mysql, MYSQL_ROW row) {

  SDL_Surface * surfaceBackground = NULL;
  SDL_Surface * surfacePokemonPlayer = NULL;
  SDL_Surface * surfacePokemonAdv = NULL;
  SDL_Texture * textureBackground = NULL;
  SDL_Texture * texturePokemonPlayer = NULL;
  SDL_Texture * texturePokemonAdv = NULL;
  SDL_Surface * text = NULL;
  SDL_Texture * textureText = NULL;
  SDL_Surface * surfaceChoseActionFight = NULL;
  SDL_Texture * textureChoseActionFight = NULL;
  SDL_Surface * surfaceCurseur = NULL;
  SDL_Texture * textureCurseur = NULL;
  SDL_Surface * surfaceSelect = NULL;
  SDL_Texture * textureSelect = NULL;
  SDL_Surface * surfaceChoseAttack = NULL;
  SDL_Texture * textureChoseAttack = NULL;
	Pokemon tab[6];

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++){
				tab[i].comp[j].text = NULL;
		}
		tab[i].img = NULL;
	}

  int fight = fightDisplay(config, tab, &surfaceChoseAttack, &textureChoseAttack, &surfaceSelect, &textureSelect, &surfaceChoseActionFight, &textureChoseActionFight, &surfaceCurseur, &textureCurseur, &text, &textureText, font, mysql, row, renderer, &surfaceBackground, &textureBackground, &surfacePokemonPlayer, &texturePokemonPlayer, &surfacePokemonAdv, &texturePokemonAdv);
  closeFightDisplay(tab, &surfaceChoseAttack, &textureChoseAttack, &surfaceSelect, &textureSelect, &surfaceChoseActionFight, &textureChoseActionFight, &surfaceCurseur, &textureCurseur, &text, &textureText, &surfaceBackground, &textureBackground, &surfacePokemonPlayer, &texturePokemonPlayer, &surfacePokemonAdv, &texturePokemonAdv);

  return fight;
}

// free surface and texture used in menu
void closeFightDisplay (Pokemon tab[6], SDL_Surface ** surfaceChoseAttack, SDL_Texture ** textureChoseAttack, SDL_Surface ** surfaceSelect, SDL_Texture ** textureSelect, SDL_Surface ** surfaceChoseActionFight, SDL_Texture ** textureChoseActionFight, SDL_Surface ** surfaceCurseur, SDL_Texture ** textureCurseur, SDL_Surface ** text, SDL_Texture ** textureText, SDL_Surface ** surfaceBackground, SDL_Texture ** textureBackground, SDL_Surface ** surfacePokemonPlayer, SDL_Texture ** texturePokemonPlayer, SDL_Surface ** surfacePokemonAdv, SDL_Texture ** texturePokemonAdv) {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++){
			if (tab[i].comp[j].text != NULL){
				SDL_DestroyTexture(tab[i].comp[j].text);
			}
		}
		if (tab[i].img != NULL){
			SDL_DestroyTexture(tab[i].img);
		}
	}

	if (*surfaceChoseAttack != NULL)
    SDL_FreeSurface(*surfaceChoseAttack);
  if (*textureChoseAttack != NULL)
    SDL_DestroyTexture(*textureChoseAttack);

	if (*surfaceSelect != NULL)
    SDL_FreeSurface(*surfaceSelect);
  if (*textureSelect != NULL)
    SDL_DestroyTexture(*textureSelect);

	if (*surfaceChoseActionFight != NULL)
    SDL_FreeSurface(*surfaceChoseActionFight);
  if (*textureChoseActionFight != NULL)
    SDL_DestroyTexture(*textureChoseActionFight);

	if (*surfaceCurseur != NULL)
		SDL_FreeSurface(*surfaceCurseur);
	if (*textureCurseur != NULL)
		SDL_DestroyTexture(*textureCurseur);

  if (*text != NULL)
    SDL_FreeSurface(*text);
  if (*textureText != NULL)
    SDL_DestroyTexture(*textureText);

  if (*surfaceBackground != NULL)
    SDL_FreeSurface(*surfaceBackground);
  if (*textureBackground != NULL)
    SDL_DestroyTexture(*textureBackground);

  if (*surfacePokemonPlayer != NULL)
    SDL_FreeSurface(*surfacePokemonPlayer);
  if (*texturePokemonPlayer != NULL)
    SDL_DestroyTexture(*texturePokemonPlayer);

  if (*surfacePokemonAdv != NULL)
    SDL_FreeSurface(*surfacePokemonAdv);
  if (*texturePokemonAdv != NULL)
    SDL_DestroyTexture(*texturePokemonAdv);
}
