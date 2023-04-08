//Raphael Kusuma
//Lab 5 - Week1
//5:15 - 8:00pm R

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

/*File Summary :
* This file defines the priority queue or pqueue
*/
typedef struct pqueue
{
    int count;
    int length; 
    void **data; //Array of entries
    int (*compare)(); //The compare function
} PQ;

/* createQueue
* Summary : This function creates the priority queue using the pqueue struct,
* it initializes length, count, and the array of entries, along with the compare function.
* 
* Runtime : O(1)
*/
PQ *createQueue(int (*compare)())
{
    PQ *pq;
    pq = malloc(sizeof(pq));

    assert(pq != NULL);

    pq->count = 0;
    pq->length = 10; //Inital length of 10
    pq->data = malloc(sizeof(void*)*pq->length);
    pq->compare = compare; 

    return pq;

}

/* destroyQueue
* Summary : This function destroys the priority queue, it starts
* by freeing the memory allocated to each entry in the array, then
* freeing the memory allocated to the array, then finally
* freeing the entire pq struct
*
* Runtime : O(n)
*/

void destroyQueue(PQ *pq)
{
    int i;

    for(i = 0; i < pq -> count; i++)
        free(pq->data[i]); //Freeing the entries in the array first
    free(pq->data); //Freeing the Array itself
    free(pq); //Freeing the priority queue
}


/* numEntries
* Summary : This function returns the amount of entries in the priority queue,
* basically just returning pq->count.
* 
* Runtime : O(1);
*/
int numEntries (PQ *pq)
{
    return pq->count; //pq->count holds the number of entries, just return it.
}

/* addEntry
* Summary : This function adds an entry to the priority queue.
*
* Runtime : O(log(n))
*/
void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL && entry != NULL);

    if(pq -> count >= pq -> length) //Checking if the count exceeds the length of the array
    {
        pq->data = realloc(pq->data, sizeof(void*)*pq->length+1); //Reallocating the size for 1 extra element
        pq->length++; //Increasing pq->length according to the max amount of elements stored
    }

    pq->data[pq->count] = entry; //Set the entry to the last part to prep for reheap.

    pq->count++;
}

/* removeEntry
* Summary : This function removes an entry in the priority queue.
*
* Runtime : O(log(n))
*/
void *removeEntry(PQ *pq)
{
    assert(pq != NULL);

    void *temp = pq->data[0]; //Saving the data on the root into a temp variable.

    pq->count--;
}

//Lecture Heap Notes
//Left Child = 2*i + 1
//Right Child = 2*i + 2
//Parent = (i-1)/2