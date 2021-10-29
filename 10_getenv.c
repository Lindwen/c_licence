/* getenv.c */
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *terminal; char * login;
    terminal = getenv("TERM");
    login=getenv("LOGNAME");
    printf("Vous êtes connectes sous le nom de %s \n", login);
    printf("Le terminal est ");
    if(terminal==NULL)
    printf("inconnu\n");
    else
    printf("un %s\n", terminal);
    exit(0);
}
