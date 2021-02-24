src/pokemon: bdd/createdb
	gcc src/*.c -o src/PokeC -I /usr/include/mariadb -lmysqlclient -lSDL2_ttf $(shell sdl2-config --cflags --libs)

bdd/createdb:
	gcc bdd/createdb.c -o bdd/createdb -I /usr/include/mariadb -lmysqlclient
