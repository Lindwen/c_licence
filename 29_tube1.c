/* tube1.c*/
#include <stdio.h>
void main(){
char c; 
int p[2];
int nb_lus;

pipe(p);        /* creation du tube */

close(p[1]);    /* descripteur en ecriture non utilisé - le fermer*/

if((nb_lus = read(p[0],&c,1)) == -1 ) 
    perror("Erreur lecture dans tube");
else if(nb_lus==0)  
    printf("Pas de caractere lu \n");
    printf("processus termine\n");
}