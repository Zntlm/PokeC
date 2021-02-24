#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int displayCommande (char ** commande);
int countSpace (char * buffer);
void cutCommande (char * buffer, char ** commande);

int main (int argc, char ** argv) {

	char ** commande = NULL;
	char buffer[7][128] = {"apt install libsdl2-dev", "apt install libsdl2-ttf-dev", "apt install libmariadb-dev", "apt install libmariadb-dev-compat", "service mysql start", "make", "./bdd/createdb"};
	int count = 0;

  for (int i = 0; i < 7; i++) {

    count = countSpace(buffer[i]);

  	commande = malloc(sizeof(*commande) * count);

  	cutCommande(buffer[i], commande);

  	if(displayCommande(commande))
  		return 0;

  	free(commande);
  }

	return 0;
}

// Cut buffer and affect each part in commande table
void cutCommande (char * buffer, char ** commande) {

	int i;
	char * strToken;

	strToken = strtok(buffer, " ");
	commande[0] = strToken;

	for (i = 1; strToken != NULL; i++) {
		strToken = strtok(NULL, " ");
		commande[i] = strToken;
	}
}

// Count space in buffer
int countSpace (char * buffer) {

	int count;
	long unsigned int i;
	int espace;

	for (i = 0, espace = 0, count = 1; i < strlen(buffer); i++){
		if (buffer[i] == ' ') {
			if (!espace){
				espace = 1;
				count++;
			}
		} else {
			espace = 0;
		}
	}

	return count;
}

// Execute commande
int displayCommande (char ** commande) {

	pid_t childpid = fork();

	if (childpid == 0) {
		execvp(commande[0], &commande[0]);
		return 1;
	}

	wait(&childpid);
	return 0;

}
