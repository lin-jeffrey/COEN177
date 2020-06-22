/*
Name: Jeffrey Lin
Date: April 7,2020
Title: Lab 2
Description: this program runs a ls command as a child process before the parent process compeletes.
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
  if(pid == 0)
    {
      execlp("/bin/ls", "ls", NULL); //ls command
      exit(0);
    }
  else{
    // Parent process
    int returnStatus;
    waitpid(pid, &returnStatus, 0); //waits until child process is complete then runs the parent process
    if (returnStatus == 0)  // Verify child process terminated without error.  
    {
       printf("Child Complete\n");
    }
    if (returnStatus == 1)      
    {
       printf("Child Incomplete\n");   
    }
    for (i=0;i<100;i++) {
      printf("\t \t \t Parent Process %d \n",i);
      usleep(n);
    }
  }
  return 0;
}

