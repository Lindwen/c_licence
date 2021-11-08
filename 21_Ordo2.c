//Ordo2.c
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

#define Max 3

pthread_t tid[Max];
pthread_attr_t attr[Max];


void *routine (void *num) {
struct sched_param p;
int politique;
int cp=0; 

usleep(10);
printf("Thread %d \n", num);

pthread_getschedparam(tid[(int)num], &politique, &p);

printf("la priorite courante de la thread fille est : %d\n", p.sched_priority);
switch (politique){
case SCHED_OTHER : printf("la thread fille se trouve dans la file SCHED_OTHER\n");
	break;
	
case SCHED_FIFO : printf("la thread fille se trouve dans la file SCHED_FIFO\n");
	break;
	
case SCHED_RR : printf("la thread fille se trouve dans la file SCHED_RR\n");
	break;
}
while (cp<=100) {cp++; }
}

// M A I N
int main() {
int a;
int  num;
struct sched_param param;

for (num=0; num<Max; num++) {
	a=pthread_attr_init(&attr[num]);
	if (a==-1) 	{ printf("erreur initialisation d'attributs\n");
			exit(0);
			}
		
	a=pthread_create(tid+num, &attr[num], routine, (void *)num);
	if (a==-1) { printf("erreur de creation de thread\n");
			exit(0);
	}
}

for (num=0; num<Max; num++) {
param.sched_priority=num+3;
pthread_setschedparam(tid[num], SCHED_RR, &param);
printf("Modif pour Thread %d : prio : %d\n", num, param.sched_priority);
}

for (num=0; num<Max; num++) {
pthread_join(tid[num], NULL); 
a=pthread_attr_destroy(&attr[num]);
if (a==-1) { printf("erreur de suppression d'attributs\n");
		exit(0);
	}
}
	
printf("attributs supprimes\n");
exit(0);
}
