/* fichier */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

char chaine[20];
int main(void)
{
    int descript;
    //descript = open("toto.txt", O_RDWR, 0);
    descript = open("toto.txt", O_RDWR, 0);

    if(fork() == 0)
    {       /* processus fils */
        write(descript, "ab", 2);
        sleep(20);
        read(descript, chaine, 2);
        printf("chaine lue par le fils: %s\n\n", chaine);
    }
    else
    {       /* processus pere */
        sleep(10);
        read(descript, chaine, 2);
        printf("chaine lue par le pere: %s\n", chaine);
        write(descript, "AB", 2);
        //wait(NULL)
        sleep(10);
    }
    return 0;
}
