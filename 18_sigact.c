/* sigact.c */
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>

char minuscule = 'a', majuscule = 'A';
int desc, i, cpt_fils = 1, cpt_pere = 1;
struct sigaction action;

void handPere() { /* handler pour SIGUSR1 installe par le pere */
for(i=1; (i <= cpt_pere) && (majuscule <= 'Z'); i++)   {
		write(desc, & majuscule, 1);
		majuscule++;
}
cpt_pere ++;
}

void handFils() {	/* handler pour SIGUSR1 installe par le fils */

for(i=1; (i <= cpt_fils) && (minuscule <= 'z'); i++)  {
		write(desc, & minuscule, 1);
		minuscule ++;
}
cpt_fils ++;
}

void main() {
int i, PID, PPID;

desc = open("toto", O_RDWR, 0);

if ((PID=fork()) == -1){perror("erreur sur fork"); exit(1);} 
else if (PID == 0)	/* processus fils */
	{
	/*installe son handler d'interception de SIGUSR1*/
	action.sa_handler = handFils;
	sigaction(SIGUSR1, &action, NULL);
	PPID = getppid();
	for(i=1; i <= 7; i++) {
		 pause();
		 usleep(100000); 	  /* dort pendant 100 ms */
		 kill(PPID, SIGUSR1); /* envoie SIGUSR1 a son pere */
		}
	exit(0);
	}

	else  /* processus pere */
	{
	/* installe son handler d'interception de SIGUSR1*/
	action.sa_handler = handPere;
	sigaction(SIGUSR1, &action, NULL);
	for (i=1; i <= 7; i++) {
		 usleep(100000);
		 kill(PID, SIGUSR1);  /* envoie SIGUSR1 a son fils */
		 pause();
		}
	close(desc);
system("cat toto"); 	/* affichage du fichier toto */
	exit(0);
	}
}
