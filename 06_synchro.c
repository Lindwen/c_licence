#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    if (fork() == 0) {
        printf("fin du procesus fils de N° %d\n", getpid());
        exit(2);

    }
    sleep(15);
}
