#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int m=2;

void main(void)
{
    int i, pid;
    printf("m=%d\n", m);
    pid = fork();

    if (pid > 0)
    {
        for (i = 0; i < 5; i++)
        {
            //sleep(1);
            m++;
            printf("\nje suis le processus père: %d, m=%d\n", i, m);
            //sleep(1);

        }
        
    }

    if (pid == 0)
    {
        for (i = 0; i < 5; i++)
        {
            m = m*2;
            printf("\nje suis le processus fils: %d, m=%d\n", i, m);
            //sleep(2);
        }
        
    }

    if (pid < 0)
    {
        printf("Problème de creation par fork()\n");
    }

}
