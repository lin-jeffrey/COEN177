/*
Name: Jeffrey Lin
Date: April 7,2020
Title: Lab 2
Description: This program creates 2 threads and prints 0 to 100
*/

#include <stdio.h>      /*prinf, stderr*/
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /*fork*/
#include <stdlib.h>     /*atoi*/
#include <errno.h>      /*errno*/
#include <pthread.h>    /*thread*/
/* main function with command-lin arguments to pass */

void* threadFirst(void *i){
  int n = *((int *) i); //turns argument into int
  for(int i = 0; i < 100; i++){
    printf("\t \t \t First Thread %d \n",i);
    usleep(n);
  }
  return 0;
}

void* threadSecond(void *i){
  int n = *((int *) i);
  for(int i = 0; i < 100; i++){
    printf("\t \t \t Second Thread %d \n",i);
    usleep(n);
  }
  return 0;
}


int main(int argc, char *argv[]) {
  int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay

  int *arg = malloc(sizeof(*arg)); //allocates memory for pass through arguements
  *arg = n;
  
  pthread_t thread_id1, thread_id2;
  pthread_create(&thread_id1, NULL, threadFirst,arg); //creates threads
  pthread_create(&thread_id2, NULL, threadSecond,arg);
  pthread_join(thread_id1, NULL); //execute threads
  pthread_join(thread_id2, NULL);
  pthread_exit(NULL);	  //exit threads
  return 0;
}
