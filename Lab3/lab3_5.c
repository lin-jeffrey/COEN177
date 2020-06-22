/*
# Name: Jeffrey Lin
# Date: 4/14/2020
# Title: Lab3 - Part 5
# Description: This program implements the producer/consumer problem
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 

void consumer(FILE *pipeDownstream){
  int n,k;
  
  //loop until no more messages on pipe
  while(1) {
    int n = fscanf(pipeDownstream, "%d", &k);	//gets message from pipe
    if(n == 1)
		printf("Consumer removed: %d\n", k);
    else break;
  }
  fclose(pipeDownstream);
  exit(0);
}

void producer(FILE *pipeUpstream){
  int i;
  for(i = 1; i <= 25; i++) {
    fprintf(pipeUpstream, "%d ", i);		//puts message on pipe
	printf("Producer created: %d\n", i);
  }
  fclose(pipeUpstream);
  exit(0);
}

int main()
{
  int pd[2];
  FILE *pipeUpstream, *pipeDownstream;

  //initializing pipe
  pipe(pd);
  pipeDownstream  = fdopen(pd[0], "r"); //read
  pipeUpstream = fdopen(pd[1], "w"); //write

  //creates produer
  if(fork() == 0) {
    fclose(pipeDownstream); //close the downstream
    producer(pipeUpstream);
  }
  
  //creates consumer
  else if(fork() == 0) {
    fclose(pipeUpstream);	//close the upstream
    consumer(pipeDownstream);
  }

  //closes pipes
  fclose(pipeDownstream);
  fclose(pipeUpstream);
  
  return 0;
}