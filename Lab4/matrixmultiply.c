//Name: Jeffrey Lin
//Date: 4/21/2020
//Title: Lab4
//Description: This program multiplies two matricies of size N,M,L using N*L threads.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define N 15
#define M 10
#define L 15

//initialize matrix A,B,C
int matrixA[N][M];
int matrixB[M][L];
int matrixC[N][L];

struct threadData{
   int i; //row
   int j; //column
};

//function declaration
void *multiply(void *param); 

int main(int argc, char *argv[]) {
	
	//fill matrix A with random numbers between 0-9
	srand(time(NULL));
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++)
			matrixA[i][j] = rand() % 10;
	}
	//fill matrix B with random numbers between 0-9
	//srand(time(NULL));
	for(int i = 0; i < M; i++){
		for(int j = 0; j < L; j++)
			matrixB[i][j] = rand() % 10;
	}
	
	//prints out Matrix A
	printf("Matrix A \n");
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++)
				printf("%d ", matrixA[i][j]);
		printf("\n");
	}
	
	//prints out Matrix B
	printf("\nMatrix B \n");
	for (int i = 0; i < M; i++){
		for (int j = 0; j < L; j++)
				printf("%d ", matrixB[i][j]);
		printf("\n");
	}
	

   for(int i = 0; i < N; i++) {
      for(int j = 0; j < L; j++) {
         //for each thread it gets a row of matrix A and column of matrix B
         struct threadData *data = (struct threadData *) malloc(sizeof(struct threadData));
         data->i = i;
         data->j = j;
		 
         //initialize thread variables
         pthread_t tid;
         pthread_attr_t attr; 
         pthread_attr_init(&attr);
         //Create thread which calls multiply
         pthread_create(&tid,&attr,multiply,data);
		 //parent thread must wait for all threads
         pthread_join(tid, NULL);
      }
   }
   printf("\nMain thread done.\n");

   //Print out the resulting matrix
   printf("\nMatrix C \n");
   for(int i = 0; i < N; i++) {
      for(int j = 0; j < L; j++) {
         printf("%d ", matrixC[i][j]);
      }
      printf("\n");
   }
}

//function will multiply the row of matrix A and column of matrix B
void *multiply(void *arg) {
	//fill struct with data from function call
   struct threadData *data = arg;
   int temp = 0;
	//Row multiplied by column and added to sum
   for(int x = 0; x< M; x++){
      temp += matrixA[data->i][x] * matrixB[x][data->j];
   }
   //fill corresponding x,y in matrix C with the sum
   matrixC[data->i][data->j] = temp;
   //exit thread when complete
   pthread_exit(0);
}