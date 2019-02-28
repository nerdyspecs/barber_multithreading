#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define CHAIRS 5
#define DELAY 100000
sem_t mutex,customers,barbers;/*Three semaphors*/

int waiting=0;/*The number of customers waiting for haircuts*/
int customerNum=0;
int currentCustomer=0;

void barber(void *arg);
void customer(void *arg);
void delay();

int main(int argc,char *argv[])
{

	pthread_t stylistThread;
	pthread_t customerThread;
	/*Semaphore initialization*/
	sem_init(&mutex,0,1);
	sem_init(&customers,0,0);
	sem_init(&barbers,0,0);

	/*creating barber thread*/
	pthread_create(&stylistThread,NULL,(void *)barber,NULL);
	
	/*creating customer thread*/
	int i=0;
	for (i = 0; i <100; i++)
	{
		pthread_create(&customerThread,NULL,(void *)customer,NULL);
	}	
	pthread_join(customerThread,NULL);
	pthread_join(stylistThread,NULL);
	printf("jobs done lets go home\n");
	return 0;
}

void delay(){
	int i =0;
	while(i<DELAY){
		i++;
	}
}

void barber(void *arg)
{
	printf("barber created\n");
	while(1)
	{
		sem_wait(&customers);         
		sem_wait(&mutex);
		waiting--;
		sem_post(&mutex);
		sem_post(&barbers);
		printf("Barber is cutting hair for customer %d\n",currentCustomer);
		currentCustomer++;
		delay();
		printf("----done cutting %dth customer----\n",currentCustomer);
		if (currentCustomer == 100 && waiting == 0){
			printf("Thats the %dth customer, and there are %d customers waiting\n",currentCustomer,waiting);
			break;
		}
	}
}

void customer(void *arg)
{
	while(1)
	{
		sem_wait(&mutex);
		if(waiting<CHAIRS)
		{
			waiting++;
			printf("Customer%d added to waiting room\n",customerNum);
			customerNum++;
			sem_post(&mutex);
			sem_post(&customers);
			sem_wait(&barbers);
			break;
		}
		else
			sem_post(&mutex);
			delay();
	}
}
