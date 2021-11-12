#include <stdio.h>

int main()
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        switch (fork())
        {
        case -1:
            fprintf(stderr, "Erreur dans %d\n", getpid());
            perror("fork");
            exit(1);
            break;

        case 0: /* On est dans un fils */
            for (j = 0; j < 10; j++)
            {
                printf("%d", i);
                fflush(stdout);
            }
            exit(0);

        default:; /* On est dans le pere; ne rien faire */
        }
    }

    for (i = 0; i < 10; i++)
    {
        wait(NULL);
    }

    exit(0);
}
