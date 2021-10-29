#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int p;

    p=fork();

    if (p > 0)
    {
        printf("processus pèsre: %d-%d-%d\n", p, getpid(), getpid());
    }

    if (p == 0)
    {
        printf("processus fils: %d-%d-%d\n", p, getpid(), getpid());
    }

    if (p < 0)
    {
        printf("Probleme de création par fork()\n");
    }

    system("ps -l");

    return 0;
}

