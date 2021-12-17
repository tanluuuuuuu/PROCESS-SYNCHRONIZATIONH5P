#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

int sells = 0, products = 0;
sem_t sem1, sem2;

// sell <= products <= sells + 91 + 10
// 	sem1	    sem2 

void *processA(void* mess)
{
	while(1)
	{
		sem_wait(&sem1); // sell <= products
		sells++;
		printf("sells = %d\n", sells);
		sem_post(&sem2);
	}
}

void *processB(void* mess)
{
	while(1)
	{
		sem_wait(&sem2); // products <= sells + 101
		products++;
		printf("products = %d\n", products);
		sem_post(&sem1);
	}
}

int main()
{
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 101);
	pthread_t pA, pB;
	pthread_create(
		&pA,
		NULL,
		&processA,
		NULL
	);
	pthread_create(
		&pB,
		NULL,
		&processB,
		NULL
	);
	while(1){}
	return 0;
}
