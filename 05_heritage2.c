#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <fcntl.h>

int d;

int main(void)
{
    d = open("toto.txt", O_CREAT | O_WRONLY, 0640);
    printf("descript=%d\n", d);

    if (fork() == 0)
    {
        write(d, "ab", 2);
    }
    else
    {
        sleep(1);
        write(d, "AB", 2);
        //wait(NULL);
    }    

    return 0;
}

