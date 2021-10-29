/* env.c */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    int k;
    printf("Appel avec %d paramètres\n", argc);
    printf("Le nom de la commande est %s\n", argv[0]);
    printf("Les arguments de la commandes sont les suivants :");
    for (k = 1; k < argc; k++) printf("%s ", argv[k]);
    printf("\n Les variables d'environnements sont :\n");
    for (k = 0; envp[k]!=NULL; k++) printf("%s\n", envp[k]);
    
    exit(0);
}
