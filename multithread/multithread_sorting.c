#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include<windows.h>
#define LENGTH 300

int x_list[LENGTH];

typedef struct{
	
	int begin ;
	int end ;
	
}parameters;

parameters *data = (parameters*) malloc(sizeof(parameters));
parameters *data2 = (parameters*) malloc(sizeof(parameters));


void merge(int i, int j)
{
	int narray[j-i+1], nk = 0;
        int mid = (i+j)/2;
        int k = i;
        int l = mid +1 ;


        while(k <= mid && l <= j) {
                if (x_list[k] > x_list[l])
                        narray[nk++] = x_list[l++];
                else                    
                        narray[nk++] = x_list[k++];
        }

        while(k <= mid) {
                narray[nk++] = x_list[k++];
        }

        while(l <= j) {
                narray[nk++] = x_list[l++];
        }

        for (k = 0; k < (j-i+1) ; k++)
                x_list[i+k] = narray[k];

}


void shuffle(int *arr, int min, int max)
{
    int size = max-min + 1; // poker size  1000 - 0 + 1 => 1001 
    int i =0 , p1 = 0, p2 = 0, tmp = 0;
    
 
    // arrange the poker[Size]
    int * Poker = (int*)malloc(sizeof(int) * size);
    for(i=0 ; i<size; ++i){
    	Poker[i] = i ;
	}
        
        
    // shuffing 
    for(i=0; i<size; ++i)
	{
        p1 = (int)(rand() / (RAND_MAX+1.0) * size);
        p2 = (int)(rand() / (RAND_MAX+1.0) * size);

        // swap two poker
        tmp = Poker[p1];
        Poker[p1] = Poker[p2];
        Poker[p2] = tmp;
    }
    
    for(i=0; i<LENGTH; ++i){
    	x_list[i] = Poker[i];
	}    
    free(Poker); // release poker
   
}



// bubble sort 
void *sorted(void *arg)
{	

	Sleep(2000); // wait a second
	int i=0,j=0,temp=0;
	 // get the data
	parameters *data = (parameters *) arg;
	parameters *data2 = (parameters *) arg;
	
	int low = data->begin;
	int high = data-> end;
	int mid = low + (high - low) / 2;
	int length_list = high - low + 1 ;
	

	//start sorting 
	for(i=low; i<=high; i++)
	{	
		for(j=i+1; j<=high; j++)
		{
			if(x_list[i] > x_list[j])
				{			
					temp = x_list[i];
					x_list[i] = x_list[j];
					x_list[j] = temp;
				}
		}						
	}
		
}



int main(int argc, char **argv){
	int counter = 0 ;
	
	while(counter<6){
			counter = counter + 1 ;
		// initialize the thread 
		pthread_t thread1, thread2, thread3; 
	
		int low = 0;
		int high = LENGTH -1; 
		//int mid = low +(high - low) / 2;
		int mid=(low+high)/2 ;
		
		//generate random numbers 
		//set the range of the random numbers
		Sleep(1000); // wait a second
		printf("\n Generate 300 random numbers ...\n");
		int min = 0 ;
		int max = 1000;
		int i = 0;
		srand((unsigned)time(NULL));
	    shuffle(x_list, min, max); //shuffle
	    
	    printf("\n________________Oringial_________________\n");
	    for(i=0; i<LENGTH; i++)
		{
			printf("%d ",x_list[i]);
		} 
		printf("\n");
	
		
		// left arrary 
		data -> begin = low;
		data -> end = mid;
		pthread_create(&thread1,NULL,&sorted,data);
	
		// right array 
		data2 -> begin = mid + 1 ;
		data2 -> end = high;
		pthread_create(&thread2,NULL,&sorted,data2);
		
		// merge  
		//merge(low, high);
	
		// thread ending 
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		merge(low, high);
		
	
		// print the result
	    printf("\n________________Rusult ________________\n");
		for(i=0; i<LENGTH; i++)
		{
			printf("%d ",x_list[i]);
		} printf("\n");
		printf("\n(%d)\n\n",counter); 
		sleep(1);
	}
	
		
}
