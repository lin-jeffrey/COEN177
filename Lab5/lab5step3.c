//# Name: Jeffrey Lin
//# Date: April 28, 2020
//# Title: Lab5 - Step 3
//# Description: The producer consumer problem using semamphores and mutex

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

//initialize variables
sem_t *full;
sem_t *empty;
pthread_mutex_t mutex;
int in = 0;
int out = 0;
int buffer[10];

void *producer(void *prodNum)
{   
	
    int item = rand()%100; 				//Produce an random item numbered 0-100
    sem_wait(empty);					//lock empty semaphore
    pthread_mutex_lock(&mutex);			//lock mutex
    buffer[in] = item;					//put item on buffer 
    printf("Producer %d produced item: %d\n", *((int *)prodNum),buffer[in]);
    in = (in+1)%10;						//increments to the next buffer slot 
    pthread_mutex_unlock(&mutex);		//unlock mutex
    sem_post(full);						//unlock full semaphore
	return (NULL);
}

void *consumer(void *consumerNum)
{   
    sem_wait(full);						//lock full semaphore
    pthread_mutex_lock(&mutex);			//lock mutex
    int item = buffer[out];				//get item from buffer
    printf("Consumer %d consumed item: %d\n",*((int *)consumerNum),item);
    out = (out+1)%10;					//increments to the next buffer slot
    pthread_mutex_unlock(&mutex);		//unlock mutex
    sem_post(empty);					//unlock empty semaphore
	return (NULL);
}

int main()
{   
    pthread_t pro[10];									//declaring 10 threads for consumers
	pthread_t con[10];									//declaring 10 threads for producers
    pthread_mutex_init(&mutex, NULL);					//initialize mutex
	empty = sem_open("empty", O_CREAT, 0644, 10);		//initialize empty semaphore
	full = sem_open("full", O_CREAT, 0644, 0);			//initialize full semaphore

	//to label each producer consumer such that number does not change
    int a[10] = {0,1,2,3,4,5,6,7,8,9}; 

	//create 10 producers and consumers
    for(int i = 0; i < 10; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 10; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

	//wait for producer to finish
    for(int i = 0; i < 10; i++) {
        pthread_join(pro[i], NULL);
    }
	//wait for consumers to finish
    for(int i = 0; i < 10; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);		//release mutex lock
	sem_unlink("empty");				//destroy empty semaphore
	sem_unlink("full");					//destory full semaphore

    return 0;
}