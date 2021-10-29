#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int p;

    p=fork();

    if (p==0) printf("je suis le processus fils\n");
    if (p>0) printf("je suis le processus père\n");

    return 0;
}

