#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

enum { SIZE = 10 };

sem_t empty, full;
sem_t mutex;
//pthread_mutex_t mutex;
int BUF[SIZE], num;

void *producer() {
    while (1) {
	sleep(1);
	sem_wait(&empty);
	//pthread_mutex_lock(&mutex);
	sem_wait(&mutex);
	BUF[num++] = 1;
	printf("produce a product, buffer has %d products.\n", num);
	//pthread_mutex_unlock(&mutex);
	sem_post(&mutex);
	sem_post(&full);
    }
}

void *consumer() {
    while (1) {
	sem_wait(&full);
	//pthread_mutex_lock(&mutex);
	sem_wait(&mutex);
	BUF[num--] = 0;
	printf("consume a product, buffer has %d products.\n", num);
	//pthread_mutex_unlock(&mutex);
	sem_post(&mutex);
	sem_post(&empty);
	sleep(1);
    }
}

int main() {
    pthread_t pro, con;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    //pthread_mutex_init(&mutex, NULL);
    sem_init(&mutex, 0, 1);
    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);
    pthread_join(pro, NULL);
    pthread_join(con, NULL);
    return 0;
}
