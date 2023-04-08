//Raphael Kusuma
//Lab 5 - Week1
//5:15 - 8:00pm R

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

/*File Summary :
* This file defines the priority queue or pqueue implemented with a
* min heap. The lowest value goes to the root.
*/
typedef struct pqueue
{
    int count; //The amount of entries in the array
    int length; //Max amount of entries 
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
    pq = malloc(sizeof(PQ));

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
    assert(pq != NULL);
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
* Runtime : O(1)
*/
int numEntries (PQ *pq)
{
    assert(pq != NULL);

    return pq->count; //pq->count holds the number of entries, just return it.
}

/* addEntry
* Summary : This function adds an entry to the priority queue.
* It also reheaps up once an entry is added, the entry is added to the lowest point of the list
* and is pushed up depending on the value of the parent node.
*
* Runtime : O(log(n))
*/
void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL && entry != NULL);

    int index = pq->count; //Keeping track of index
    void *temp;
    
    if(pq -> count == pq -> length) //Checking if the count exceeds the length of the array
    {
        pq->data = realloc(pq->data, (sizeof(void*)*(pq->length*2))); //Reallocating double the size as max entries
        pq->length = pq->length*2; //Increasing pq->length according to the max amount of elements to bestored
    }

   
    pq->data[pq->count] = entry; //Set the entry to the last part to prep for reheap up.
     
    while((pq->compare)(pq->data[(index-1)/2],pq->data[index]) > 0) //While the parent is bigger than entry 
    {
	    temp = pq->data[(index-1)/2]; //The parent node is entered into a temp variable.
	    pq->data[(index-1)/2] = pq->data[index]; //Entry is moved up
	    pq->data[index] = temp; //Parent node moved down
	    index = (index-1)/2; //Decrement index
    }
    pq->count++;
}

/* removeEntry
* Summary : This function removes an entry in the priority queue. It reheaps down
* once an entry has been removed to preserve the order of the array
*
* Runtime : O(log(n))
*/
void *removeEntry(PQ *pq)
{
    assert(pq != NULL);

    int index = 0; //Keeping track of index we are looking at

    int leftchild = 1; //Index of left child 

    int rightchild = 2; //Index of right child 

    void *temp;

    void *bottomNode = pq->data[pq->count-1]; //Storing the last node of the heap to the top.

    void *ftemp = pq->data[0]; //Original Root

    pq->count--;
    while(2*index+leftchild <= pq->count)//While loop to make sure there exists a child
    {	 	
	int indexmin = 2*index+leftchild; //We set the initial index to the left child

	//Start by comparing sizes of the child nodes
	if(2*index+rightchild <= pq->count) //if the right child exists
	{	    
	    if((pq->compare)(pq->data[2*index+rightchild], pq->data[2*index+leftchild]) < 0) //Comparing left and right child. (If right child is smaller)   
		indexmin = 2*index+rightchild; //The smallest value is the right child	    
	}

	//Then we can start swapping nodes and fixing the heap.	
        if((pq->compare)(bottomNode, pq->data[indexmin]) > 0) //parent node is bigger than temp (the smallest child)
	{
	    temp = pq->data[indexmin];
	    pq->data[indexmin] = bottomNode; //Putting the smallest variable into the parent index 
	    pq->data[index] = temp;
	    index = indexmin;//Since we swapped, we need to update index "location of bottomNode"
	}
	else
	    break; //This break means that the children nodes are bigger than the "parent" and therefore, the parent node is the min
    }   
    
    
    pq->data[index] = bottomNode; //Setting the final location of the "bottomNode".

    return ftemp; //Returning the original root of the heap
}

//Lecture Heap Notes
//Left Child = 2*i + 1
//Right Child = 2*i + 2
//Parent = (i-1)/2
