#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define NUMBER_OF_THREADS 3

void *sort_array(void *params);
void *merge_array(void *params); 

int list[SIZE];
int result[SIZE];

typedef struct
{
    int startIndex;
    int stopIndex;
} parameters;


void *sort_array(void *params)//sort the input array
{
    parameters* p = (parameters *)params;
    int begin = p->startIndex;
    int end = p->stopIndex+1;

    printf("Input: \n");
    for(int i = begin; i < end; i++){
        printf("%d, ", list[i]);
    }

    printf("\n");

    int temp=0;

    for(int i=begin; i< end; i++)
    {
        for(int j=begin; j< end-1; j++)
        {

            if(list[j] > list[j+1])
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;

            }
        }
    }

    printf("Output: \n");
    for(int k = begin; k< end; k++){
            printf("%d, ", list[k]);
    }

    for(int i=begin; i<end; i++)
    {
            result[i] = list[i];
    }
    printf("\n");

    pthread_exit(NULL);
}

void *merge_array(void *params)//merge the two arrays
{
    parameters* p = (parameters *)params;

    int begin = p->startIndex;
    int end = p->stopIndex+1;

    int temp;
    for(int i=begin; i< end; i++)
    {
        for(int j=begin; j< end-1; j++)
        {

            if(result[j] > result[j+1])
            {
                temp= result[j];
                result[j] = result[j+1];
                result[j+1] = temp;

            }
        }
    }
    printf("\n\nFinal Output:\n");
    for(int d=begin; d<end; d++)
    {
        printf("%d, ", result[d]);
    }
    printf("\n");
    pthread_exit(NULL);
}


int main (int argc, const char * argv[])
{
    int i;
    pthread_t workers[NUMBER_OF_THREADS];
    //create 100 random integers (value <10000) saved in a list
    for(i = 0; i < SIZE; i++){
	list[i] = rand() % 10000;
    }

    //the first thread
    parameters *data = (parameters *) malloc (sizeof(parameters));


    data->startIndex = 0;
    data->stopIndex = (SIZE/2) - 1;

    pthread_create(&workers[0], 0, sort_array, data);
    //the second thread


    data = (parameters *) malloc (sizeof(parameters));
    data->startIndex = (SIZE/2);
    data->stopIndex = (SIZE - 1);

    pthread_create(&workers[1], 0, sort_array, data);
    //wait for the two threads to end

    for (i = 0; i < NUMBER_OF_THREADS - 1; i++)
        pthread_join(workers[i], NULL);
    //the merge thread


    data = (parameters *) malloc(sizeof(parameters));

    data->startIndex = 0;
    data->stopIndex = (SIZE - 1);

    pthread_create(&workers[2], 0, merge_array, data);
    //wait for the merge to end

    pthread_join(workers[2], NULL);
    return 0;
}


