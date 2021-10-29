/* perefil1.c */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int PID;
    if ((PID = fork()) == 0)
    {       /* processus fils */
        printf("1ere partie du fils \n");
        printf("\t 2eme partie du fils \n");
        printf("\t\t 3eme partie du fils \n");
        sleep(15);
    }
    else if (PID > 0)
    {       /* processus pere */
        printf("1ere partie du pere \n");
        printf("\t 2eme partie du pere \n");
        printf("\t\t 3eme partie du pere \n");
        wait(NULL);
    }
    else perror("Erreur dans fork !!!");
    return 0;
}
