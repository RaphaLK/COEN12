//Raphael Kusuma
//COEN 12L - Term Project
//5:15-8:00pm R

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#define MAX_COUNT 10
//Doubly Linked
//Head & Tail ptr
//Same size arrays within nodes -- Let's say array is 10;
//Doesn't matter where to search


/* File Summary
 * --------------------------------
 * This file implements a doubly linked list of circular arrays.
 */
typedef struct node
{
    struct node *next;
    struct node *prev;
    void **data;
    int acount; //This count keeps track of the number of arrays filled in each node
    int start; //int value to keep track of where we started
} NODE;

typedef struct list
{
    int count; //This count keeps track of the amount of nodes in the list.
    NODE *head;
    NODE *tail;
    //int (*compare)();  -> I'm not sure if we need a compare func 

} LIST;

/* createList
 * Summary : Creates and intializes the list 
 */

LIST *createList(void)
{
    LIST *lp;

    lp = malloc(sizeof(LIST));
    assert(lp != NULL);

    lp -> count = 1; //Initialize count at 1;

    lp -> head = malloc(sizeof(NODE));

    lp -> head -> next = NULL; 
    lp -> head -> prev = NULL;
    lp -> head -> acount = 0;

    lp -> head -> data = malloc(sizeof(void*)*(MAX_COUNT)); 
    lp -> tail = lp -> head;

    return lp;

}


/* destroyList
 * Summary : Deallocates memory associated with the list pointed by lp
 *
 * Runtime : O(n)
 */
void destroyList(LIST *lp)
{
    assert(lp != NULL);

    NODE *p = lp -> head;
    NODE *q;

    while(p -> next != NULL)
    {
	q = p -> next;
	free(p->data);
	free(p);
	p = q;
    }
    
    free(lp);

}

/* numItems
 * Summary : Returns the number of items in the list pointed by lp
 * We can assume that if there's more than two nodes, all middle nodes MUST
 * be full. 
 * Runtime : O(n)
 */
int numItems(LIST *lp)
{
    assert(lp != NULL);
    int total = 0;
    NODE *h = lp -> head;

    //Traverse each node and total up their acount (array count)
    while(h != NULL)
    {
	total += h -> acount;
	h = h -> next;
    } 

    return total;

    //UNDER THIS WAS AN OLD ATTEMPT (MIGHT TRY TO GET IT TO WORK AGAIN)
    /*
    //Case 1 : Head = Tail (one node)
    if(lp -> head == lp -> tail)
    {
	printf("numitems Case 1\n");
	return h -> acount;
    }
    //Case 2 : More than one node
    else
    {
	printf("Start of numitems case 2\n");
	headcount = lp -> head -> acount;
	tailcount = lp -> tail -> acount;
	total = ((((lp -> count)-2)*MAX_COUNT) + headcount + tailcount);
    }
    printf("End of numitems\n");
    return total;
    */   	
}

/* addFirst
 * Summary : Adds an element to the start of the list pointed
 * by lp
 *
 * Runtime: O(1)
 
 */
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);

    NODE *p = malloc(sizeof(NODE));

    assert(p != NULL);
       
    if(lp -> head -> acount == MAX_COUNT) //First node is full
    {
	//Allocate a new node and make it the first
	p -> data = malloc(sizeof(void*)*MAX_COUNT); //Initialize the array
	p -> acount = 0;
	p -> start = MAX_COUNT-1;
	
	//Setting up prev and next addresses for p
	p -> prev = NULL;
	p -> next = lp -> head -> next;

	//We're moving the head pointer back to shift the list forward	
	lp -> head = lp -> head -> prev;
	
	lp -> head = p;
	p -> data[p -> start] = item;
	lp -> count++;
    }
    else
	lp -> head -> data[lp -> head -> start] = item;

    p -> acount++;
    p -> start--; //Decrement start
}
/* addLast
 *
 * Summary : Adds an element to the end of the list pointed 
 * by lp.
 *
 * Runtime : O(1)
 */
void addLast(LIST *lp, void *item)
{
    assert(lp != NULL);
    
    NODE *p = malloc(sizeof(NODE));
    
    assert (p != NULL);
    //Last node is full -> create a new one
    if(lp -> tail -> acount == MAX_COUNT)
    {
	p -> data = malloc(sizeof(void*)*MAX_COUNT);
	p -> start = 0;
	p -> acount = 0;

	//Setting p -> next and p -> last
        p -> prev = lp -> tail;
	p -> next = NULL;

	lp -> tail -> next = p; //The initial last node should be connected to p	

	lp -> tail = lp -> tail -> next; //p will be the new tail;

	lp -> tail -> data[0] = item;

	lp -> count++; //Increment number of nodes
    }
    else
	lp -> tail -> data[(lp -> tail -> start + lp -> tail -> acount + MAX_COUNT ) % MAX_COUNT] = item; //Add the item at the index. 
    
    lp -> tail -> acount++; //We add in the end anyways, so just increment at the end

    return;
}

/* removeFirst
 * Summary : Removes the first element of the list pointed to by lp
 * and returns it.
 * 
 * Runtime : O(1)
 */
void *removeFirst(LIST *lp)
{ 

    assert(lp != NULL && lp -> count > 0);
     
    NODE *p = lp -> head;
    void *temp; //Storing the deleted data

    //Node is empty
    if(lp -> head -> acount == 0)
    {
	lp -> head = lp -> head -> next;
	lp -> head -> prev = NULL;
	
	free(p -> data); //Deallocating the array of p
	free(p); //Deallocating the empty node

	lp -> count--;
    }
    //Node has elements

    temp = lp -> head -> data[lp -> head -> start]; //temp will point at the start
    
    lp -> head -> data[lp -> head -> start] = NULL; //Removing element from the array

    lp -> head -> start = ((lp -> head -> start + 1) % MAX_COUNT); 
    
    lp -> head -> acount--;

    return temp;
}
/* removeLast
 * Summary : Removes the last element of the list pointed to by lp
 * and returns it.
 *
 * Runtime : O(1)
 */
void *removeLast(LIST *lp)
{
    assert(lp != NULL && lp -> count > 0);
    
    NODE *p = lp -> tail;
    void *temp; //Store the deleted variable here
    
    //Case 1 : Node is empty
    if(lp -> tail -> acount == 0)
    {
	lp -> tail = lp -> tail -> prev;
	lp -> tail -> next = NULL;

	free(p->data);
	free(p);

	lp -> count--;
    }
    
    temp = lp -> tail -> data[(lp -> tail -> start + lp -> tail -> acount -1) % MAX_COUNT];

    lp -> tail -> data[(lp -> tail -> start + lp -> tail -> acount -1) % MAX_COUNT] = NULL;

    lp -> tail -> acount--;
	
    return temp;
}
/* getItem
 * Summary : Returns the item at position index in the list pointed by lp;
 * the index must be within range.
 *
 * Runtime : O(n)
 */
void *getItem(LIST *lp, int index)
{
    assert(lp != NULL);
    
    NODE *p = lp -> head;
    
    //Traverse the whole list looking for the indexed position
    //Decrement index based on the count of the arrays in the nodes
    while(index >= p -> acount)
    {
	index -= p -> acount;
	p = p -> next;
    }

    return p -> data[(p -> start + index) % MAX_COUNT];
}
/* setItem
 * Summary : Sets the item in the list pointed by the index given.
 * Same thing like getItem, but instead of returning the location, item gets put into the
 * location.
 *
 * Runtime : O(n)
 */ 
void setItem(LIST *lp, int index, void *item)
{
    assert(lp != NULL);
    
    NODE *p = lp -> head;

    while(index >= p -> acount)
    {
	index -= p -> acount;
	p = p -> next;
    }
    p -> data[(p -> start + index) % MAX_COUNT] = item;
}
