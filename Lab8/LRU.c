//this program implements the LRU page replacement algorithm
//run by executing cat accesses.txt | ./LRU (insert num)

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
    	int page_num = atoi(pageCache); 			// Stores number read from file as an int
		totalRequests++;							//increase the total num of requests
		
		if(!inTable(page_num, cache, C_SIZE)){		//if page num is not in the cache
			printf("Page %d caused a page fault.\n", page_num);
			totalFaults++;							//increment the amount of faults
			if(cacheIndex < C_SIZE){				//if the cache is not full yet
				for(int x = cacheIndex; x > 0; x--){//if there is already items in the cache we shift them up
					cache[x] = cache[x-1];
				}
				cache[0] = page_num;				//add page num to cache at the newest spot 
				cacheIndex++;
			}	
			else{									//if page num is in cache
				for(int y = C_SIZE-1; y > 0; y--){	//we shift all nums in cache forward eliminating the oldest one
					cache[y] = cache[y-1];			
				}
				cache[0] = page_num;				//add page num to newest spot in cache
			}
		}
		else{										//if page num is in cache
			int pageNumIndex;
			for(int j = 0; j < C_SIZE; j++){		//find the position of the page num currently in cache
				if(cache[j] == page_num){
					pageNumIndex = j;
					break;
				}
			}
			for(int k = pageNumIndex; k > 0; k--){	//increment all positions before the page num position
				cache[k] = cache[k-1];
			}
			cache[0] = page_num;					//add page num back at newest spot on cache
		}
    }
	float missRate = (float)totalFaults/totalRequests;	//calculate miss rate
    printf("Total Page Faults: %d \n", totalFaults);	//print total faults
	printf("Total Requests: %d \n", totalRequests);		//print total requests
	printf("Fault Rate: %f \n", missRate);				//print miss rate
    return 0;
}
