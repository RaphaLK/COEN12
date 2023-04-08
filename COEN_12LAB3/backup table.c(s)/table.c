//Raphael Kusuma
//Lab 3 - Generic
//COEN12-L 5:15R

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

/* This file defines the struct set, it defines the functions for adding,
 * removing and searching for elements in the hashtable impelemented. The functions
 * for creating and destroying the set are also defined here.
 * */

typedef struct set
{
    int length;
    int count;
    void **data;
    char *flag;
    int (*compare)();
    unsigned (*hash)();
}SET;

/* Summary : This function creates the set, it allocates memory for the data, flag array and the set itself.
 * It also initialized the flag array to flag all parts of the table as 'E' or empty.
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
    sp->compare = compare;
    sp->hash = hash;
    sp->data = malloc(sizeof(void*)*maxElts);
    sp->flag = malloc(sizeof(char*)*maxElts);
    

    for(i = 0; i < sp->length; i++)
	sp->flag[i] = 'E'; //Setting all flags to "Empty"

    assert(sp != NULL);
    return sp;
}

/* Summary : Destroys the set, it frees all the memory allocated by *CreateSet
 * 
 * Runtime : O(1)
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);
    
    //Freeing memory that was allocated in *createSet
    free(sp->data); 
    free(sp->flag);
    free(sp);
}

/* Summary : This function uses linear probing to conduct a search through the hash table.
 * It returns either the first deleted location, or the location which is filled and matches the 
 * input, or returns an empty spot.
 *
 * Runtime : Best - O(1), Worst - O(n)
 */
static int search(SET *sp, void *elt, bool *found)
{
    int locn, i, delstore;
    int index = (*sp->hash)(elt) % sp->length;
    delstore = -1;

    for(i = 0; i < sp->length; i++)
    {
	locn = (index+i) % sp->length; //Linear Probing

        if(sp->flag[locn] == 'F') //Case 1 : Spot is full
	{
	    if((*sp->compare)(sp->data[locn],elt) == 0)
	    {
		*found = true;
		return locn;
	    }
	}
	else if(sp->flag[locn] == 'D') //Case 2 : Spot is Deleted
	{
	    if(delstore == -1)
		delstore = locn; //Saves first deleted spot
	}
	else if(sp->flag[locn] == 'E')//Case 3 : Spot is empty
	    break;
    }
    *found = false;

    if(delstore == -1)
	return locn; //Return last spot if no delete flags are found

    return delstore; //Returns first delete spot found
}
/* Summary : Returns the number of elements in the table.
 *
 * Runtime : O(1)
 */
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}
/* Summary : Adds an element to the hash table, uses linear probing to either find the first
 * deleted location to add or an empty slot. If a duplicate is found, it won't be added.
 *
 * Runtime : Best - O(1), Worst - O(n)
 */
void addElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found);
    if(!found)
    {
        sp->data[index] = elt;
        sp->flag[index] = 'F'; //Setting flag to "Found"
        sp->count++;
    }
    return;
}
/* Summary : This removes an element in the hash table. Linear probing is used
 * to find the element in the hash table which is the same as the one passed as an argument.
 *
 * Runtime : Best - O(1), Worst - O(n)
 */
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found);;

    if(found == true)
    {
        sp->flag[index] = 'D'; //Setting flag to "Delete"
        sp->count--; 
    }
    return;
}

/* Summary : Finds an element in the hash table and returns it.
 * If not found, it returns NULL.
 *
 * Runtime : Best - O(1), Worst - O(n)
 */
void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;

    int index = search(sp, elt, &found);
    
    if(found == true)
        return sp->data[index];
    
    else 
        return NULL;
}

/* Summary : Gets a copy of all elements in the hashtable and moves it to an array.
 *
 * Runtime : O(n)
 */
void *getElements(SET *sp)
{
    assert(sp != NULL);
    void **a;
    int i,j = 0;

    a = malloc(sizeof(void*)*sp->count);

    for(i = 0; i < sp->length; i++)
    {
	if(sp->flag[i] == 'F')
	{
	    a[j] = sp->data[i];
	    j++;
	}
    }
    return a;

}
