#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main (int argc, char ** argv) {

  MYSQL mysql;
  int error;
  FILE * fileScript;
  char request[512];

  memset(request, 0, 512);

  // init MySQL
  if (!mysql_init(&mysql)) {
    printf("init\n");
    return 1;
  }

  if (!mysql_real_connect(&mysql, "localhost", "root", "", NULL, 80, NULL, 0)) {
    printf("connect : %d > %s\n", mysql_errno(&mysql), mysql_error(&mysql));
    return 1;
  }

  if (mysql_query(&mysql, "CREATE DATABASE pokemon")){
    error = mysql_errno(&mysql);
    if (error != 1007){
      printf("create db : %d > %s\n", error, mysql_error(&mysql));
      return 1;
    }
  }

  error = 0;
  if (mysql_query(&mysql, "CREATE USER 'user'@'localhost' IDENTIFIED BY 'azerty'")){
    error = mysql_errno(&mysql);
    if (error != 1396){
      printf("create user : %d > %s\n", error, mysql_error(&mysql));
      return 1;
    }
  }

  if (error != 1396){
    if (mysql_query(&mysql, "GRANT ALL PRIVILEGES ON * . * TO 'user'@'localhost'")){
      printf("grant all privileges : %d > %s\n", mysql_errno(&mysql), mysql_error(&mysql));
      return 1;
    }

    if (mysql_query(&mysql, "FLUSH PRIVILEGES")){
      printf("flush privileges : %d > %s\n", mysql_errno(&mysql), mysql_error(&mysql));
      return 1;
    }
  }

  mysql_close(&mysql);

  if (!mysql_init(&mysql)) {
    printf("init\n");
    return 1;
  }

  if (!mysql_real_connect(&mysql, "localhost", "user", "azerty", "pokemon", 80, NULL, 0)) {
    printf("connect : %d > %s\n", mysql_errno(&mysql), mysql_error(&mysql));
    return 1;
  }

  fileScript = fopen("script.sql", "r");

  fseek(fileScript, 0, SEEK_SET);

  while (!feof(fileScript)) {
    fgets(request, 512, fileScript);
    if (mysql_query(&mysql, request)){
      error = mysql_errno(&mysql);
      if (error != 1050) {
        printf("script : %d > %s\n", error, mysql_error(&mysql));
        return 1;
      }
    }
  }

  fclose(fileScript);

  fileScript = fopen("insert.sql", "r");

  fseek(fileScript, 0, SEEK_SET);

  while (!feof(fileScript)) {
    fgets(request, 512, fileScript);
    if (mysql_query(&mysql, request)){
      error = mysql_errno(&mysql);
      if (error != 1062) {
        printf("insert : %d > %s\n", error, mysql_error(&mysql));
        return 1;
      }
    }
  }

  fclose(fileScript);

  mysql_close(&mysql);

	return 0;
}
