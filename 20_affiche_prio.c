/* affiche_prio.c */
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>

void proc_fils (int pid) {
int i;
   	 printf(" le processus %d commence a s'executer \n",pid);
    	usleep(100);
    	
	for (i=0 ; i<10000 ; i++) {
		if ((i==4000) || (i==9000) ) {  
			printf(" le processus %d vient de liberer le processeur\n ", pid) ;
			sched_yield() ; 
		}
}
}

void politique_ordo(int pid) {
int ordo;

printf ("La politique d'ordo du processus %d est : ", pid);
ordo= sched_getscheduler(pid);
switch (ordo) {
	case SCHED_FIFO :  printf(" SCHED_FIFO\n ") ; break ;
	case SCHED_RR : 	 printf(" SCHED_RR\n") ; break ;
	case SCHED_OTHER : printf("SCHED_OTHER\n ") ; 
   }
printf("Les priorites minimale et maximale de cette politique d'ordo sont : %d et %d \n", sched_get_priority_min(ordo), sched_get_priority_max(ordo)); 
}


void changer_poli(int pid, int prio) {
struct sched_param  p1, p2;
int res;

/* changer la priorite d'un processus */
p1.sched_priority=prio;
if ((res=sched_setscheduler(pid, SCHED_RR, &p1))==0) {
	sched_getparam(pid,&p2);
	printf ("\n le processus %d a change de file d'ordo et est maintenant dans la SCHED_RR avec la priorite %d \n",pid, p2.sched_priority);
	}
}

// M A I N
int main (void){
int pidf1, pidf2;

struct timespec intervalle;

if ((pidf1=fork())==0) { // processus fils 1
   	proc_fils(getpid());
    } 
    
if ((pidf2=fork())==0) { // processus fils 2
   	proc_fils(getpid());
    } 
 
if (pidf1==-1 || pidf2==-1) { printf("erreur\n"); exit(1); }
    
/* processus pere*/
 	
printf("\n\tpriorites initiales des processus crees %d et %d sont : %d et %d.\n ", pidf1, pidf2, getpriority(PRIO_PROCESS, pidf1),  getpriority(PRIO_PROCESS,pidf2)); 
politique_ordo(pidf1); 
politique_ordo(pidf2);
 
changer_poli(getpid(), 2);
changer_poli(pidf1, 3);
changer_poli(pidf2, 5);

printf("Les priorites minimale et maximale de la politique SCHED_RR sont : %d et %d \n", sched_get_priority_min(SCHED_RR), sched_get_priority_max(SCHED_RR)); 
		
sched_rr_get_interval(getpid(),&intervalle);
printf("quantum de temps de la file d'ordo des processus :  %d milli-sec\n", intervalle.tv_nsec/1000000);
exit(0);
} 