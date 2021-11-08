/* SigInt.c */
#include <signal.h>
#include <stdio.h>

struct sigaction action;
int cpte = 0;

void hand()
{
    cpte++;
    (cpte == 1) ? printf("1er ") : printf("%deme ", cpte);
    printf("appui sur Ctrl-c\n");
    if(cpte==5)
    {
        printf("\n Arret au prochain coup\n");
        action.sa_handler = SIG_DFL;
        sigaction(SIGINT, &action, NULL);
    }
}

void main()
{
    action.sa_handler = hand;
    sigaction(SIGINT, &action, NULL);
    while(1);
}