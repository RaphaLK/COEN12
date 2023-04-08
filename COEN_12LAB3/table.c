//Raphael Kusuma
//Lab 3 - Strings
//COEN 12-L 5:15 R

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

/* The struct set is defined here. Functions for adding, searching, removing elements
 * into a hash table is implemented here. Along with destroying and creating the set.
 *
 */
typedef struct set
{
    int length;
    int count;
    char **data;
    char *flag;
}SET;
/* Summary : This function creates a SET with a length of maxElts, memory
 * for data and flag arrays are allocated here.
 *
 * Runtime : O(1) -> Best Case & Worst Case
 *
 */
SET *createSet(int maxElts)
{
    SET *sp;
    int i;
    sp = malloc(sizeof(SET));

    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    sp->flag = malloc(sizeof(char)*maxElts);

    for(i = 0; i < sp->length; i++)
	sp->flag[i] = 'E'; //Setting all flags to empty

    assert(sp != NULL);
    return sp;
}

/* Summary : This function destroys the set and frees all allocated data.
 *
 * Runtime : O(1) -> Best Case and Worst Case
 * 
 */

void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;

    for(i = 0; i < sp->length; i++)
	if(sp->flag[i] == 'F')
	    free(sp->data[i]); //For loop to free ONLY filled spots

    free(sp->data);
    free(sp->flag);
    free(sp);
}

/* Summary : Hash function. Returns a hash value.
 *
 * Runtime : O(1) -> Best Case and Worst Case
 */
unsigned strhash(char *s)
{
    unsigned hash = 0;

    while(*s != '\0')
        hash = 31 * hash + *s++;

    return hash;
}

/* Summary : Search function, returns either an empty spot, or the first deleted spot found or
 * a filled spot with the same element as elt.
 *
 * Runtime : O(1) -> Best Case, O(n) -> Worst Case
 */
static int search(SET *sp, char *elt, bool *found)
{
    int locn, i, delstore;
    int index = strhash(elt)%sp->length;
    delstore = -1;

    for(i = 0; i < sp->length; i++)
    {
	locn = (index+i)%sp->length; //Linear Probing

        if(sp->flag[locn] == 'F') //Case 1 : Filled spot and same element found
        {
	    if(strcmp(sp->data[locn],elt) == 0)
	    {
            *found = true;
            return locn;
	    }
        }
	else if(sp->flag[locn] == 'D') //Case 2 : Deleted spot
	{
	    if(delstore == -1) 
		delstore = locn; //Storing location of where the first deleted spot is
	}
	else if(sp->flag[locn] == 'E') //Case 3 : Spot is empty
	    break;
    }
    *found = false;

    if(delstore == -1)
	return locn; //Return last spot if no deleted spots are found

    return delstore; //Returns first deleted spot
}
/* Summary : Returns the number of elements in the hash table.
 * Basically just sp->count.
 *
 * Runtime : O(1)
 */
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

/* Summary : Adds an element to the hash table. Linear probing is used to find
 * a key. 
 *
 * Runtime : Best - O(1), Worst O(n)
 */
void addElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found);
    if(!found) //If same element not found
    {
        sp->data[index] = strdup(elt); //Duplicate string into index
        sp->flag[index] = 'F'; //Set flag of index to "Filled"
        sp->count++;
    }
    return;
}
/* Summary : Removes an element from the hash table. Linear probing is used to find
 * a filled spot with the exact same element as *elt passed as an argument.
 *
 * Runtime : Best - O(1), Worst - O(n)
 */
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found); //Searching Hashtable
    if(found == true) //If same element is found
    {
        free(sp->data[index]); //Freeing index
        sp->flag[index] = 'D'; //Setting flag of index to "Deleted"
        sp->count--; 
    }
    return;
}
/* Summary : Finds an element in the table and returns it if found, else returns NULL.
 *
 * Runtime : Best - O(1), Worst O(n)
 */

char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;

    search(sp, elt, &found);
    
    if(found == true)
        return elt; //Returns elt if same string is present.
    
    else 
        return NULL;
}
/* Summary : Returns a copy of the array with all the element sin the hash table.
 *
 * Runtime : O(n)
 */
char **getElements(SET *sp)
{
    assert(sp != NULL);

    char **a;
    int i, j = 0;

    a = malloc(sizeof(char*)*sp->count); //Allocates memory equal to amount of space taken in the table.

    for(i = 0; i < sp->length; i++)
    {
	if(sp->flag[i] == 'F')
	{
	    a[j] = strdup(sp->data[i]); //Only copies the filled spots
	    assert(a[j] != NULL);
	    j++;
	}
    }
    return a;

}
