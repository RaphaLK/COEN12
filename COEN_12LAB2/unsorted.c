//Raphael Kusuma
//Lab 2 - Unsorted
//COEN12L 5:15-8:00pm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

typedef struct set
{
    int count;
    int length;
    char **data;
}SET;

SET *createSet(int maxElts)
{
    SET *sp;

    sp = malloc(sizeof(SET));
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);

    return sp;
}
/* Function : destroySet
 * Frees all elements in the set and destroys it
 *
 * Big-O Runtime : O(n)
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    
    for(i = 0; i < sp->count; i++)
        free(sp->data[i]);
    
    free(sp->data);
    free(sp);

    return;
}
/* Function : search (PRIVATE)
 * Searches for same words in the set
 *
 * Big-O Runtime : O(n)
 */
static int search(SET *sp, char *elt, bool *found)
{
    int i;
    int flag;

    for(i = 0; i < sp->count; i++)
    {
        flag = strcmp(elt, sp->data[i]); //Compares elt to words present in set

        if(flag == 0)
        {
            *found = true;
            return i;
        }
	else
	    *found = false;
    }

    return false;
    
}
/* Function : numElements
 * Returns the number of elements in the set.
 * 
 * Big-O Runtime : O(1)
 */
int numElements(SET *sp)
{
    assert(sp != NULL);

    return(sp->count);
}

/* Function : addELements
 * Adds an element to the set
 *
 * Big-O Runtime : O(n)
 */
void addElement(SET *sp, char *elt)
{
    int i;
    bool check;
    
    assert(sp != NULL);

    search(sp, elt, &check);

    if(check == false || sp->count == sp->length) //If word not found in the set, it's added to the bottom
    {
	sp->data[sp->count] = strdup(elt);
	sp->count += 1;
    }

    check = false;
    return;
}

/* Function : removeElement
 * Removes an element from the set at idx
 *
 * Big-O Runtime : O(n)
 */
void removeElement(SET *sp, char *elt)
{
    int i, idx;
    bool check, flag;
    
    assert(sp != NULL);

    idx = search(sp, elt, &check);
    
    if(check == true)
    {
	free(sp->data[idx]);
	sp->data[idx] = sp->data[sp->count-1]; //fills in empty spot caused by deletion by last element
	sp->count--;
    }
    
    return;

}
/* Function : findELement
 * Searches for an element that is in the set and returns it
 * Returns NULL if not found
 *
 * Big-O Runtime : O(n)
 */
char *findElement(SET *sp, char *elt)
{
    int i;
    bool check;

    assert(sp != NULL);

    search(sp, elt, &check);
        
    if(check == true)    
	return elt;
    else
	return NULL;
}
/* Function : getElements
 * Creates another array and copies all elements of sp into that array
 * and returns it
 *
 * Big-O Runtime : O(1)
 */
char **getElements(SET *sp)
{
    char **a;

    assert(sp != NULL);

    a = malloc(sizeof(char*)*(sp->count));
    assert(a != NULL);
    memcpy(a, sp->data, sizeof(char*)*(sp->count));

    return a;
}
