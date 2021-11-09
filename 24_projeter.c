// projeter.c
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h> /* pour la fonction mmap */
#include <sys/types.h>
#include <fcntl.h> /* pour la fonction open */

main() {
char * fichier;
int i, N, test;
N=35;
int fd=open("fichier.txt", O_RDWR);
/* projection de N caracteres du fichier en memoire */
fichier = mmap(0,N, PROT_READ + PROT_WRITE, MAP_SHARED, fd, 0);

printf("\nLa partie du fichier projetee:\n");
for (i=0; i<N; i++) { printf("%c", fichier[i]);}
printf("\n");

/* conversion en majuscules */
for (i=0; i<N; i++) {
	if ((fichier[i]>='a') && (fichier[i]<='z'))
	fichier[i]=fichier[i]-'a'+'A';
	}

printf("\nLa partie du fichier projetee apres conversion :\n");
for (i=0; i<N; i++) { printf("%c", fichier[i]);}
printf("\n");

test = msync(fichier, N, MS_SYNC + MS_INVALIDATE);
printf("\nTest : %d \n", test);

munmap(fichier, N);
close(fd);
}
