#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#define CHAIR 5



typedef struct cv{
	int count;
	sem_t semaphore;
}cv;

cv stylistAvailable, customerAvailable;
int cus = 0;
int sty= 0;

void mon_checkCustomer(){
	sty = sty+1;
	sem_post(&stylistAvailable.semaphore);

	if (cus == 0){
		printf("waiting for customer available\n");
	}
	sem_wait(&customerAvailable.semaphore);
	cus = cus - 1;
}

int mon_checkStylist(){
	int status = 0;
	if ( cus < CHAIR){
		if (sty == 0){
			printf("waitinf for stylist available\n");
			sem_wait(&stylistAvailable.semaphore);
			stylistAvailable.count++;
		}
		cus = cus + 1;
		printf("there is a customer available\n");
		sem_post(&customerAvailable.semaphore);
		sty = sty - 1;
		status = 1;
	}
	return status;
}

