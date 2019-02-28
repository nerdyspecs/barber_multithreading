#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#define DELAY 100000


void customer(void* arg);
void stylist(void* arg);
void delay();
void mon_checkCustomer();
int mon_checkStylist();
sem_t semaphore;

void main(void){
	pthread_t stylistThread;
	pthread_t customerThread;

	/*Semaphore initialization*/
	sem_init(&semaphore,0,0);

	/*creating customer and stylist thread*/
	pthread_create(&stylistThread,NULL,(void *)stylist,NULL);
	int i=0;
	for (int i = 0; i <100; i++)
	{
		pthread_create(&customerThread,NULL,(void *)customer,NULL);
	}

	pthread_join(customerThread,NULL);
	pthread_join(stylistThread,NULL);
	printf("jobs done lets go home\n");
}

void delay(){
	int j;
	while(j<DELAY){
		j++;
	}
}

void stylist(void *arg){
	int i = 0;
	while (1){
		mon_checkCustomer();
		printf("cutting hair\n");
		delay();
		printf("done cutting hair\n");
		i++;
		if( i == 100){
			break;
		}
	}
}

void customer(void*arg){
	while(1){
		if(mon_checkStylist() == 1){
			delay();
			break;
		}
	}
	printf("done cutting hair\n");
}