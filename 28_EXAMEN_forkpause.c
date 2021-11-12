#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void interruption(int signum)
{
    if (signum == SIGINT)
    {
        printf("UN\n");
    }
}

int main(void)
{
    int pid;

    signal(SIGINT, &interruption);
    signal(SIGALRM, &interruption);
    pid = fork();
    srand(pid);
    if (!pid)
    {
        sleep(rand() % 2);
        printf("DEUX\n");
        kill(getppid(), SIGINT);
    }
    else
    {
        alarm(5);
        sleep(rand() % 2);
        printf("TROIS\n");
        pause();
    }

    exit(EXIT_SUCCESS);
}