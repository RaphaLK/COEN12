//Raphael Kusuma
//Lab 4 - Set.c
//5:15 - 8:00 R
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#include "list.h"

/* This file uses a hashtable which holds a deque in each slot */

/* Defining struct set, with an array of lists
 */
typedef struct set
{
    int count;
    int length;
    struct list **data;
    int (*compare)();
    unsigned(*hash)();
} SET;

/* createSet
 * 
 * Summary : Function creates a set and allocates memory for the 
 * parts of the set, including the array of lists.
 *
 * Runtime : O(1)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)())
{
    SET *sp;
    int i;
    sp = malloc(sizeof(SET));

    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(struct list*)*sp->length);
    sp->hash = hash;
    sp->compare = compare;

    for(i = 0; i < sp->length; i++)
	sp->data[i] = createList(compare);

    assert(sp != NULL);

    return sp;
}
 
/* destroySet
 *
 * Summary : Destroys the set, frees the data first before freeing the 
 * entire set.
 *
 * Runtime : O(1)
 */
void destroySet(SET *sp)
{
    free(sp->data);
    free(sp);
}

/* numElements
 *
 * Summary : Returns the number of elements in sp.
 *
 * Runtime : O(1)
 */
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}
/* addElements
 *
 * Summary : Adds an element to the set based on the hash value
 *
 * Runtime : O(1) or O(n)
 */
void addElement(SET *sp, void *elt)
{
    
    assert(sp != NULL && elt != NULL);
    int locn = (*sp->hash)(elt)%sp->length;
    
    if(findItem(sp->data[locn], elt) == NULL)
    {
        addFirst(sp->data[locn], elt);
        sp->count++;
    }

    return;
}
/* removeElement
 *
 * Summary : Removes an element from the set sp, uses hashing to find the 
 * element in the set for removal.
 *
 * Runtime : O(1) or O(n)
 */
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int locn = (*sp->hash)(elt)%sp->length;

    if(findItem(sp->data[locn], elt) != NULL) //Find item returns NULL if elt isnt found
    {
        removeItem(sp->data[locn], elt);
        sp->count--;
    }

    return;
}
/* findElement
 *
 * Summary : Uses hashing to search the a list and returns an element using the hash key locn..
 *
 * Runtime : O(1) or O(n)
 *
 */
void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int locn = (*sp->hash)(elt)%sp->length; //Hashing
    
    return findItem(sp->data[locn], elt);
}

/* getElements
 * 
 * Summary : Temp holds all the elements from one deque, then memcpy
 * is used to move all elements from temp to a, it is then incremented so
 * the data from the array of lists can be held in a single array designated as a.
 *
 * Runtime : O(n)
 */

void *getElements(SET *sp)
{
    assert(sp != NULL);
    void **a;
    void **temp;

    int i,j = 0;

    a = malloc(sizeof(void*)*sp->length);

    for(i = 0; i < sp->length; i++)
    {
	temp = getItems(sp->data[i]); //Takes all elements from one deque and puts it into temp
	memcpy(a+j, temp, sizeof(void*)*numItems(sp->data[i])); //Copies all elements from temp into a
	j += numItems(sp->data[i]); //To keep track of the increment of a's index
    }
    
    return a;
    
}


