/* tube.c */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
main(int argc, char *argv[])
{
int desc, desc2;

switch (fork()) {
case -1 : perror("fork"); exit(1);
case 0 : //fils
if ((desc=open(argv[1], O_WRONLY|O_CREAT, 0666))== -1){
  	  perror("open");
  	  exit(2);
}
close(STDOUT_FILENO); /* fermer la sortie standard */

dup(desc); /* STDOUT_FILENO pointe le meme fichier que desc */
/* dup: cree un nouveau descripteur qui pointe le meme fichier que desc, de plus le numero choisi correspond a la premiere entree libre dans la table des descripteurs, dans ce cas ce sera STDOUT_FILENO puisque l'entree correspondante est libre */
/* equivalent a : dup2(desc, STDOUT_FILENO); */
close(desc); /* fermer le descripteur desc car il est inutile */

execlp("ls", "ls", "-l", NULL);
perror("execlp");
exit(1);
 	
default : wait(NULL); //pere
 		if ((desc2=open(argv[1],O_RDONLY))==-1) {
  		 perror("open"); exit(2); }
		 close(STDIN_FILENO);
		 dup(desc2);
		 close(desc2);
		 execlp("wc", "wc", "-l", NULL);
		 perror("execlp");
		 exit(1);
 		}
}
