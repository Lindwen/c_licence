/* masque.c */
#include <stdio.h>
#include <signal.h>

struct sigaction action;

void main()
{
	action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	printf("Signaux SIGINT et SIGQUIT ignores\n");

	sleep(10);

	printf("\nRetablissement des signaux SIGINT et SINGQUIT\n");
	action.sa_handler = SIG_DFL;
        sigaction(SIGINT, &action, NULL);
        sigaction(SIGQUIT, &action, NULL);

	while(1);
}
