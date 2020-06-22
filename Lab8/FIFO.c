//this program implements the FIFO page replacement algorithm
//run by executing cat accesses.txt | ./FIFO (insert num)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//this function checks if a page number is inside the page table
int inTable(int pageNum, int *pageTable, int bufferSize){
	for(int i = 0; i < bufferSize; i++){
		if(pageNum == pageTable[i]){
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    int cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

	int totalRequests = 0; //total requests
    int totalFaults = 0; // keeps track of the total page faults
    int cacheIndex = 0; //keep track of cache index if cache is empty
	
    for(int i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i] = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); 				// Stores number read from file as an int
		totalRequests++;								//increase the total num of requests
		
		if(!inTable(page_num, cache, C_SIZE)){			//if page num is not in the cache
			printf("Page %d caused a page fault.\n", page_num);
			totalFaults++;								//increment the amount of faults
			if(cacheIndex < C_SIZE){					//if the cache is not full yet
				cache[cacheIndex] = page_num;			//add page num to cache
				cacheIndex++;
			}	
			else{										//if page num is in cache
				for(int i = 0; i < C_SIZE-1; i++){		//we shift all nums in cache up eliminating the oldest one
					cache[i] = cache[i+1];			
				}
				cache[C_SIZE-1] = page_num;				//add page num to cache
			}
		}
    }
	float missRate = (float)totalFaults/totalRequests;	//calculate miss rate
    printf("Total Page Faults: %d \n", totalFaults);	//print total faults
	printf("Total Requests: %d \n", totalRequests);		//print total requests
	printf("Fault Rate: %f \n", missRate);				//print miss rate
    return 0;
}
