#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define LENGTH 300 
#include<windows.h>

int x_list[LENGTH];

typedef struct{
	
	int begin ;
	int end ;
	
}parameters;

parameters *data = (parameters*) malloc(sizeof(parameters));
parameters *data2 = (parameters*) malloc(sizeof(parameters));


void merge(int i, int j)
{
        int mid = (i+j)/2;
        int k = i;
        int l = mid+1;

        int newArray[j-i+1], newK = 0;

        while(k <= mid && l <= j) {
                if (x_list[k] > x_list[l])
                        newArray[newK++] = x_list[l++];
                else                    
                        newArray[newK++] = x_list[k++];
        }

        while(k <= mid) {
                newArray[newK++] = x_list[k++];
        }

        while(l <= j) {
                newArray[newK++] = x_list[l++];
        }

        for (k = 0; k < (j-i+1) ; k++)
                x_list[i+k] = newArray[k];

}


void shuffle_1(int *arr, int low, int up)
{
    int i, pos1, pos2, tmp;
    int Size = up-low + 1; // poker size 
 
    // arrange the poker[Size]
    int * Poker = (int*)malloc(sizeof(int) * Size);
    for(i=0 ; i<Size; ++i) //  low to up
        Poker[i] = i+low;
    // start shuffing 
    for(i=0; i<Size; ++i){
        // randomly choose [0,Size) poker
        pos1 = (int)(rand() / (RAND_MAX+1.0) * Size);
        pos2 = (int)(rand() / (RAND_MAX+1.0) * Size);
        // swap two poker
        tmp = Poker[pos1];
        Poker[pos1] = Poker[pos2];
        Poker[pos2]=tmp;
    }
    // after shuffling , give the first n sheets to Arr 
    for(i=0; i<LENGTH; ++i)
        x_list[i] = Poker[i];
    free(Poker); // release poker
   
}





// bubble sort 
void *sorted(void *arg)
{	

	Sleep(2000); // wait a second
	printf("Start sorting....\n");
	int i=0,j=0,temp=0;
	 // get the data
	parameters *data = (parameters *) arg;
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
	while(counter < 6) {  	
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
		printf("\n Generate 3000 random numbers ...\n");
		int min = 0 ;
		int max = 1000;
		int i = 0;
		srand((unsigned)time(NULL));
	    shuffle_1(x_list, min, max); //shuffle
	    
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
		merge(low, high);
	
		// thread ending 
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);
		
	
		// print the result
	    printf("\n________________Rusult ________________\n");
		for(i=0; i<LENGTH; i++)
		{
			printf("%d ",x_list[i]);
		} printf("\n");
		printf("\n________________%d___________________\n\n",counter); 
		sleep(1);
	 }
		
}
