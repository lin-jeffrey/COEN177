//this program implements the SC page replacement algorithm
//run by executing cat accesses.txt | ./SC (insert num)

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
	int secondChanceCache[C_SIZE]; //Cache that stores second chance
    char pageCache[100]; // Cache that holds the input from test file

	int totalRequests = 0; //total requests
    int totalFaults = 0; // keeps track of the total page faults
    int cacheIndex = 0; //keep track of cache index if cache is empty
	int emptyCacheIndex = 0; 
	
    for(int i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i] = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); 					// Stores number read from file as an int
		totalRequests++;									//increase the total num of requests
		
		if(!inTable(page_num, cache, C_SIZE)){				//if page num is not in the cache
			printf("Page %d caused a page fault.\n", page_num);
			totalFaults++;									//increment the amount of faults
			if(emptyCacheIndex < C_SIZE - 1){				//if the cache is not full yet
				emptyCacheIndex++;							//increment index of the empty cache
				cache[cacheIndex] = page_num;				//add page num to cache
				secondChanceCache[cacheIndex] = 0;			//set second chance of that page num to 0 
				cacheIndex = (cacheIndex + 1) % C_SIZE; 	//utilize a circular array so we wrap the index if the index is beyond the cache size
			}	
			else{											//if cache is full we have to see if there are second chances
				while(secondChanceCache[cacheIndex] == 1){	//if second chance is true
					secondChanceCache[cacheIndex] = 0;		//we set the second chance back to 0
					cacheIndex = (cacheIndex + 1) % C_SIZE;	//increment index to see if another page num has a second chance
				}
				cache[cacheIndex] = page_num;				//place page num on cache
				secondChanceCache[cacheIndex] = 0;			//set second chance to 0
				cacheIndex = (cacheIndex + 1) % C_SIZE;		//increment index
			}
		}
		else{												//if item is already in table
			for(int i = 0; i < C_SIZE; i++){				//loop until we find the index of the page num 
				if(page_num == cache[i]){
					secondChanceCache[i] = 1;				//set second chance to 1
					break;
				}		
			}
		}
    }
	float missRate = (float)totalFaults/totalRequests;	//calculate miss rate
    printf("Total Page Faults: %d \n", totalFaults);	//print total faults
	printf("Total Requests: %d \n", totalRequests);		//print total requests
	printf("Fault Rate: %f \n", missRate);				//print miss rate
    return 0;
}
