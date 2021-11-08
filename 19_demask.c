/* demask.c */
#include <stdio.h>
#include <signal.h>
sigset_t   Ens1, Ens2, Ens3;
int sig;

void main()  {
/* Construction de l'ensemble Ens1 = {SIGINT, SIGQUIT, SIGUSR1} */
sigemptyset(&Ens1);
sigaddset(&Ens1,SIGINT);
sigaddset(&Ens1,SIGQUIT);
sigaddset(&Ens1, SIGUSR1);
/* Installation du masque ens1 */
sigprocmask(SIG_SETMASK, &Ens1, NULL);
printf("Masquage des signaux SIGINT, SIGQUIT, SIGUSR1 \n ");
sleep(15);
/* Affichage des signaux pendants masqués */
printf("Voici les signaux pendants: ");
sigpending(&Ens2);
for (sig=1; sig < NSIG; sig++)
if (sigismember(&Ens2,sig))  printf(" %d  ", sig);
putchar('\n');
sleep(15);	
/* Demasquage des signaux */
printf("Demasquage des signaux \n");
sigemptyset(&Ens1);
sigprocmask(SIG_SETMASK, &Ens1, NULL);
printf("Fin du processus\n");
}
