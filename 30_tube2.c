/* tube2.c */
#include <stdio.h>
#include <signal.h>

struct sigaction action;

void capture() {printf("\007 SIGPIPE a ete recu par le processus %d \n", getpid());}

void main() {
int p[2];

action.sa_handler = capture;   
sigaction(SIGPIPE,&action,NULL);

printf("Mon pid est %d\n", getpid());

pipe(p);  

close(p[0]); /* fermer le descripteur du tube en lecture */

/*Tentative d'ecriture dans un tube sans lecteur ==> reception de SIGPIPE  */
if( write(p[1],"jsk",3)== -1 ) 
perror("Erreur ecriture dans tube - ca ne doit pas s'afficher si SIGPIPE est générée corectement et il n'y avait pas de handler");
     else printf("Je ne dois jamais passer par la");
}