/* perefils.c */
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int PID;
    if ((PID = fork()) == 0)
    {       /* processus fils */
        printf("Le fils: mon pid est %d, le pid de mon papa est %d\n", getpid(), getpid());
        printf("\t\t fork a retourné au fils la valeur %d\n", PID);
    }
    else if (PID > 0)
    {       /* processus père */
        printf("Le père: mon pid est %d, le pid de mon papa a moi est %d\n", getpid(), getpid());
        printf("\t\t fork a retourné au père la valeur %d\n", PID);
        sleep(2);
    }
    else("Erreur dans fork !!!");
    return 0;
}
