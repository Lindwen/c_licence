#include <stdio.h>
#include <signal.h>

void hand(int signum)
{
	printf("appui sur Ctrl-C\n");
	printf("Arret au prochain coup\n");
	signal(SIGINT, SIG_DFL);
}

int main(void)
{
	signal(SIGINT, hand);
	for (;;) { }
	return 0;
}