//Raphael Kusuma
//Lab 4
//COEN12L 5:15R

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"
/* FILE DESCRIPTION
* ==================
* list.c implements a deque using a 
* doubly circular linked list.
*/

//Defining both structs NODE and LIST
typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list
{
    int count;
    struct node *head;
    int (*compare)();
} LIST;

/* createList
* Summary : Creates a new list, allocates memory for list and nodes.
* Runtime : O(1)
*/
LIST *createList(int(*compare)())
{
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);

    lp -> count = 0;
    lp -> compare = compare;
    lp -> head = malloc(sizeof(NODE)); 
    
    assert(lp -> head != NULL);

    lp -> head -> next = lp -> head; //Setting address of head -> next to itself.
    lp -> head -> prev = lp -> head; //Setting address of head -> prev to itself.

    return lp;
}

/* destroyList
* Summary : Frees the list
* Runtime : O(n)
*/
void destroyList(LIST *lp)
{
    NODE *pDel, *pNext;

    assert(lp != NULL);
    pDel = lp -> head;
    
    do
    {
        pNext = pDel -> next;
        free(pDel);
        pDel = pNext;
    } while (pDel != lp -> head);
    
    free(lp);

    return;
}
/* numItems
* Summary : Keeps track of lp->count, it returns the number 
* of items in the list.
*
* Runtime : O(1)
*/
int numItems(LIST *lp)
{
    assert(lp != NULL);

    return lp -> count;
}
/* addFirst
 * Summary : This function adds a node to the start of the list.
 * It assigns the node to the head's next pointer.
 *
 * Runtime O(1)
 */
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL); 

    NODE *p;
    p = malloc(sizeof(NODE));

    p -> data = item; //Assigning item to p.

    p -> next = lp -> head -> next; //Assigning p -> next

    p -> prev = lp -> head; //Assigning p -> prev

    lp -> head -> next = p; //Assigning head -> next

    p -> next -> prev = p; //Assigning the prev of the node after p to p

    lp -> count++;

    return;
}
/* addLast
 * Summary : Adds a node to the end of the list, with p -> next being
 * connected to the head pointer and p -> prev connected to head -> prev
 * to create a doubly circular linked list.
 *
 * Runtime : O(1)
 */
void addLast(LIST *lp, void *item)
{   
    assert(lp != NULL && item != NULL);
    NODE *p;

    p = malloc(sizeof(NODE));

    p -> data = item;

    p -> next = lp -> head;

    p -> prev = lp -> head -> prev;

    p -> prev -> next = p;

    lp -> head -> prev = p;

    lp -> count++;

    return;
}
/* removeLast
 * Summary : Removes the last node of the list, also returns
 * the data of the deleted node. Frees the node at the end.
 *
 * Runtime : O(1)
 * 
 */
void *removeLast(LIST *lp)
{
    assert(lp != NULL);
    NODE *p;
    void *ldata;

    p = malloc(sizeof(NODE));

    p = lp -> head -> prev;

    ldata = p -> data; //Saves the data of the to-be-deleted node.

    lp -> head -> prev = p -> prev;

    free(p);

    lp -> count--; //Decrement Count

    return ldata;
}
/* removeFirst
 * Summary : Removes the first element of the list. Also returns the data
 * of the to-be-deleted node. 
 *
 * Runtime : O(1)
 */
void *removeFirst(LIST *lp)
{
    assert(lp != NULL);
    NODE *p, *q;
    void *fdata;

    p = malloc(sizeof(NODE));
    q = malloc(sizeof(NODE));
    

    p = lp -> head -> next;

    fdata = p->data; //Storing the first node's data

    q = p -> next;

    q -> prev = lp -> head;

    lp -> head -> next = q;

    free(p);

    lp -> count--; //Decrement count
    
    return fdata;
}

/* getFirst
 * Summary : Gets the data of the first node in the list
 * and returns it.
 *
 * Runtime : O(1)
 */
void *getFirst(LIST *lp)
{
    assert(lp != NULL);
    NODE *p;

    p = malloc(sizeof(NODE));

    p = lp -> head -> next; //Setting p to the node after the head ptr.

    return p -> data;
}
/* getLast
 * Summary : Gets the data of the last node in the list
 * and returns it.
 *
 * Runtime : O(1)
 */
void *getLast(LIST *lp)
{
    assert(lp != NULL);
    NODE *p;

    p = malloc(sizeof(NODE));

    p = lp -> head -> prev; //Since list is circular, move a node before head to get the last.

    return p -> data;
}
/* RemoveItem
 * Summary : Traverses the list and compares *item and the data
 * in each node. If it matches, it is removed.
 *
 * Runtime : O(n);
 */
void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE  *p;

    p = malloc(sizeof(NODE));

    p = lp -> head -> next;

    do
    {
        if((*lp->compare)(p -> data, item) == 0) //Compares the data in the node and the given data
        {
            p -> next -> prev = p -> prev; // Steps for deletion
            p -> prev -> next = p -> next;
            free(p);   
            lp -> count--; //Decrements count
            
	    break;
        }
        p = p -> next;
    } while (p -> next != lp -> head); //do - while loop to traverse the list.

}

/* findItem
 * Summary : Traverses the list and compares the data in each node
 * to item. If it matches, the data in the node is returned.
 * Otherwise, it returns NULL.
 *
 * Runtime : O(n)
 */
void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE  *p;
    p = malloc(sizeof(NODE));

    if(lp->count > 0)
    {
	p = lp -> head -> next;
	while(p != lp -> head)
	{
	    if((*lp -> compare)(p -> data, item) == 0) //If a duplicate is found, return it
		return p -> data;
	    p = p -> next; //Move on to the next node if not
	}
    }


    return NULL;
}
/* getItem
 * Summary : Creates an array and copies the data in each node
 * in the linked list into the array and returns it.
 *
 * Runtime : O(n)
 */
void *getItems(LIST *lp)
{
    void **a;
    NODE *p;
    int i = 0;


    a = malloc(sizeof(void*)*lp->count);
    p = malloc(sizeof(NODE*));

    p = lp -> head -> next;	
    while(p != lp -> head)
    {
        a[i] = p -> data; //Copies the data
        p = p -> next; //Moves p to the next node
        i++; //Increments i
    }

    return a;
}
