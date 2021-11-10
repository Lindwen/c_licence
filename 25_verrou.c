/* verrou.c */
#include <fcntl.h>
#include <unistd.h>

//https://www.hackinglinuxexposed.com/articles/20030623.html

main(){
	int desc;
	struct flock verrou, verrou2;
	if(desc=open("toto", O_RDWR)==-1) {perror("ERR: ouverture fichier");exit(1);} // Ouverture en écriture, sinon pas possible de poser un verrou exclusif

	/* verrou exclusif sur les 5 caracteres a partir du 10eme */
	verrou.l_type=  F_WRLCK; //verrou exclusif => portée disjointe de tout autre verrou
	verrou.l_whence=SEEK_SET;//à partir du début du fichier
	verrou.l_start= 15;	
	verrou.l_len=   2;	
	verrou.l_pid= getpid(); 
	if(fcntl(desc, F_SETLKW, &verrou)==-1){perror("ERR: pose verrou"); exit(1);} // F_SETLKW pose bloquante du verrou
	printf("verrou 1 pose par %d\n", getpid());
	//15 à 17

	/* verrou partage sur les 3 caracteres a partir du 18eme */
	verrou.l_type=F_RDLCK;  // Verrou partagé (plusieurs verrous peuvent se chevaucher)
	verrou.l_whence = SEEK_SET;//à partir du début du fichier
	verrou.l_start = 18;
	verrou.l_len=3;
	verrou.l_pid=getpid();
	if(fcntl(desc, F_SETLKW, &verrou)==-1){perror("ERR: pose verrou"); exit(1);} // F_SETLKW pose bloquante du verrou
	printf("verrou 2 pose par %d\n", getpid());
	//18 à 20

	/* verrou exclusif sur les 2 caracteres a partir du 5eme avant la fin */
	verrou.l_type = F_WRLCK; //verrou exclusif => portée disjointe de tout autre verrou
	verrou.l_whence = SEEK_END; //depuis la fin du fuchier
	verrou.l_start = 5;
	verrou.l_len = 2;
	verrou.l_pid=getpid();

	if(fcntl(desc, F_SETLKW, &verrou)==-1){perror("ERR: pose verrou"); exit(1);} // F_SETLKW pose bloquante du verrou
	printf("verrou 3 pose par %d\n", getpid());
	//5 à 7

	sleep(20);

	printf("Fin du processus %d\n",getpid()); /* suppression automatique du verrou*/
}
