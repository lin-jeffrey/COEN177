#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

//declare struct that contains row and column data
struct Data{
	int* x, *y, *n;
	int* matrixA[n][n];
	int* matrixB[n][n];
	int* matrixC[n][n];	
};

void *multiply(struct Data *threadData){
	int temp = 0;
	for(int i = 0; i < threadData->n; i++){
		temp += threadData->matrixA[i][threadData->x] * threadData->matrixB[threadData->y][i];
	}
	threadData->matrixC[threadData->x][threadData->y] = temp;
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]); // size of matrix
	int totalthreads = n*n;	//number of threads
	pthread_t threads[totalthreads];
	
	//declare matrices
	int	matrixA[n][n],
		matrixB[n][n], 
		matrixC[n][n];
	
	//populate matricies with random numbers between 0 and 9
	srand(time(NULL));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			matrixA[i][j] = rand() % 10;

	srand(time(NULL));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			matrixB[i][j] = rand() % 10;
	
	//prints out Matrix A
	printf("Matrix A \n");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
				printf("%d ", matrixA[i][j]);
		printf("\n");
	}
	
	//prints out Matrix B
	printf("\nMatrix B \n");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
				printf("%d ", matrixB[i][j]);
		printf("\n");
	}
	
	//create threads	
	struct Data threadData;
	int i = 0;
	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++){
			threadData = (x, y, n, matrixA, matrixB, matrixC);
			pthread_create(&threads[i], NULL, multiply, (void *) &threadData);
			i++;
		}
	}
	i = 0;
	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++){
        	pthread_join(threads[i],NULL);
			i++;
    }
	printf("Main thread done.\n");
	
	printf("\nMatrix C \n");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
				printf("%d ", matrixC[i][j]);
		printf("\n");
	}
}