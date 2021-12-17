#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

int n;
int a[1000];
int s = 0; // So luong phan tu hien tai trong mang
sem_t semPush, semPop;
pthread_mutex_t mutex;

// sell <= products <= sells + 91 + 10
// 	sem1	    sem2 

void *processPush(void* mess)
{
	while(1)
	{
		sem_wait(&semPush);
		pthread_mutex_lock(&mutex);
		int r = rand() % 1001;
		a[s] = r;
		s++;
		printf("So phan tu sau khi them: %d\n", s);
		pthread_mutex_unlock(&mutex);
		sem_post(&semPop);
	}
}

void *processPop(void* mess)
{
	while(1)
	{
		sem_wait(&semPop);
		pthread_mutex_lock(&mutex);
		int pos = (rand() % (s + 1));
		for (int i = pos; i <= s - 1; i++)
			a[i] = a[i + 1];
		s--;
		printf("So phan tu sau khi xoa: %d\n", s);
		pthread_mutex_unlock(&mutex);
		sem_post(&semPush);
	}
}

int main()
{
	printf("Nhap so phan tu toi da (n < 1000): ");
	scanf("%d", &n);

	// Gia su ban dau mang a co 0 phan tu
	sem_init(&semPush, 0, n);
	sem_init(&semPop, 0, 0);
	pthread_t pPush, pPop;
	pthread_create(
		&pPush,
		NULL,
		&processPush,
		NULL
	);
	pthread_create(
		&pPop,
		NULL,
		&processPop,
		NULL
	);
	while(1){}
	return 0;
}
