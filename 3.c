#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

int x = 0;

void *processA(void* mess)
{
	while(1)
	{
		x = x + 1;
		if (x == 20)
			x = 0;
		printf("%d\n", x);
	}
}

void *processB(void* mess)
{
	while(1)
	{
		x = x + 1;
		if (x == 20)
			x = 0;
		printf("%d\n", x);
	}
}

int main()
{
	// Gia su ban dau mang a co 0 phan tu
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
