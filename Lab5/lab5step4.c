//# Name: Jeffrey Lin
//# Date: April 28, 2020
//# Title: Lab5 - Step 4
//# Description: The producer consumer problem using condition variables

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

//initialize variables
pthread_mutex_t mutex;
pthread_cond_t itemsAvailable;
pthread_cond_t spaceAvailable;
int in = 0;
int out = 0;
int bufferItemCount;
int maxItems = 10;
int buffer[10];

void *producer(void *prodNum)
{   
    int item = rand()%100; 					//Produce an random item numbered 0-100
    pthread_mutex_lock(&mutex);				//lock mutex
	while(bufferItemCount == maxItems){					//while there is no space in the buffer
		pthread_cond_wait(&spaceAvailable, &mutex);		//wait until there is a signal that space is available
	}
    buffer[in] = item;						//put item on buffer 
    printf("Producer %d produced item: %d\n", *((int *)prodNum),buffer[in]);
    in = (in+1)%10;							//increments to the next buffer slot 
	bufferItemCount++;						//increase the count of items on the buffer
	pthread_cond_signal(&itemsAvailable);	//send the signal that there are items on the buffer
    pthread_mutex_unlock(&mutex);			//unlock mutex
	return (NULL);
}

void *consumer(void *consumerNum)
{   
    pthread_mutex_lock(&mutex);				//lock mutex
	while(bufferItemCount == 0){						//while there is no items in the buffer
		pthread_cond_wait(&itemsAvailable, &mutex);		//wait until there is a signal that items are available on the buffer
	}
    int item = buffer[out];					//get item from buffer
    printf("Consumer %d consumed item: %d\n",*((int *)consumerNum),item);
    out = (out+1)%10;						//increments to the next buffer slot
	bufferItemCount--;						//decrements the count of items on the buffer
	pthread_cond_signal(&spaceAvailable);	///send the signal that there is avaiable space on the buffer
    pthread_mutex_unlock(&mutex);			//unlock mutex
	return (NULL);
}

int main()
{   
    pthread_t pro[10];									//declaring 10 threads for consumers
	pthread_t con[10];									//declaring 10 threads for producers
    pthread_mutex_init(&mutex, NULL);					//initialize mutex

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

    return 0;
}