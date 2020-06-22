/*
Name: Jeffrey Lin
Date: April 7,2020
Title: Lab 2
Description: This program creates a parent and child processes that print 100 times.
*/

#include <stdio.h>      /*prinf, stderr*/
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /*fork*/
#include <stdlib.h>     /*atoi*/
#include <errno.h>      /*errno*/
/* main function with command-lin arguments to pass */
int main(int argc, char *argv[]) {
  pid_t  pid;
  int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
  printf("\n Before forking.\n");
  pid = fork();
  if (pid == -1) {
    fprintf(stderr, "can't fork, error %d\n", errno);
  }
  if (pid){
    // Parent process
    for (i=0;i<100;i++) {
      printf("\t \t \t Parent Process %d \n",i);
      usleep(n);
    }
  }
  else{
    // Child process
    for (i=0;i<100;i++) {
      printf("Child process %d\n",i);
      usleep(n);
    }
  }
  return 0;
}

