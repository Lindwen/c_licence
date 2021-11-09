/* lire_project.c */
#include <sys/mman.h>
#include <sys/stat.h> /* pour la fonction stat */
#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
int i, Desc, Taille;
char *AdrMem;
struct stat StructFichier;

if (argc !=2) {
	fprintf(stderr, ">>> Syntaxe : %s fichier \n", argv[0]);
	exit(1);
}

/* Ouverture du fichier en lecture seule */
if ((Desc = open(argv[1],O_RDONLY)) == -1 ) {
			perror("erreur sur open"); exit(1);
}

/* Obtention de la taille du fichier a l'aide de la fonction stat */
if (stat(argv[1], &StructFichier) == -1) {
			perror("erreur sur stat"); close (Desc); exit(1);
}
Taille = StructFichier.st_size;
printf("%d est la taille du fichier %s \n" ,Taille , argv[1]);

/* Projection en mémoire */
if ((AdrMem = (char *) mmap (NULL, StructFichier.st_size, PROT_WRITE, MAP_PRIVATE, Desc, 0)) == NULL) {
		perror ("erreur sur mmap"); close (Desc); exit(1);
}

/* On peut fermer le fichier */
close(Desc);

printf("Voici le contenu du fichier projete:\n");
for (i=0; i< Taille; i++) putchar(AdrMem[i]);

/* Liberation de l'espace memoire */
if ( munmap(AdrMem, Taille== -1)) {
		perror("erreur sur munmap"); exit(1);
}
}
