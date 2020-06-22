/*
Name: Jeffrey Lin
Date: April 7,2020
Title: Lab 2
Description: this program creates 7 processes with no parent having either 0 or 2 children.
*/

#include <stdio.h>      /*prinf, stderr*/
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /*fork*/
#include <stdlib.h>     /*atoi*/
#include <errno.h>      /*errno*/
/* main function with command-lin arguments to pass */
int main() {
  int children = 6; //to have 7 total process the parent must have 6 children
  printf("\n Parent: %d\n", getpid()); //parent process id
  
  while(children > 0){ //must have 6 children
    if(fork() == 0){ //creates first child from parent
      printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
      break;
    }
    else{
      waitpid(-1, NULL, 0);
    }
    if(fork() > 0){ //if is parent process we have to wait for the child process to complete
      waitpid(-1, NULL, 0);
      break;
    }
    else{ //second child 
      printf("Child with id: %d and its Parent id: %d \n", getpid(),getppid());
    }
    children = children - 2;
  }
  return 0;
}

