//OrdoThread.c
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t tid[1];
pthread_attr_t attr;

void *routine (void * arg) {
struct sched_param p, p1;
int politique, poli;

	pthread_attr_getschedpolicy(&attr, &politique);
	pthread_attr_getschedparam(&attr, &p); 
	
	printf("file d'ordonnancement initiale de la thread fille : " );
	switch (politique){
	case SCHED_OTHER : printf("SCHED_OTHER\n");
	break;
	
	case SCHED_FIFO : printf("SCHED_FIFO\n");
	break;
	
	case SCHED_RR : printf("SCHED_RR\n");
	break;
	}

	printf("priorite initiale de la thread fille : %d\n", p.sched_priority);
	printf("Modification des parametres d'ordonnancement dans le corps  de la thread fille\n");
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);	
	p.sched_priority=6;
	pthread_attr_setschedparam(&attr, &p);
	sleep(1);
	pthread_attr_getschedparam(&attr, &p1);
	pthread_attr_getschedpolicy(&attr, &poli);
	printf("la priorite courante de la thread fille est : %d\n", p1.sched_priority);
	switch (poli){
		case SCHED_OTHER : printf("la thread fille se trouve dans la file SCHED_OTHER\n");
		break;
	
		case SCHED_FIFO : printf("la thread fille se trouve dans la file SCHED_FIFO\n");
		break;
	
		case SCHED_RR : printf("la thread fille se trouve dans la file SCHED_RR\n");
		break;
	}
}
	
// M A I N 
int main() {
int a;

a=pthread_attr_init(&attr);
if (a==-1) { printf("erreur initialisation d'attributs\n");
		exit(0);
	}
	
a=pthread_create(tid, &attr, routine, (void *)0);
if (a==-1) { printf("erreur de creation de thread\n");
		exit(0);
	}

pthread_join(tid[0], NULL); 
a=pthread_attr_destroy(&attr);
if (a==-1) { printf("erreur de suppression d'attributs\n");
		exit(0);
	}
	
printf("attributs supprimes\n");
exit(0);
}
