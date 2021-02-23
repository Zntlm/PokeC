../pokemon: test/createdb
	gcc ../*.c -o ../pokemon -I /usr/include/mariadb -lmysqlclient -lSDL2_ttf $(shell sdl2-config --cflags --libs)

test/createdb:
	gcc test/createdb.c -o test/createdb -I /usr/include/mariadb -lmysqlclient
