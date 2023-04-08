//Raphael Kusuma
//Lab 2 -- Sorted
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

/* Function : createSet
 * Creates a set.
 *
 * Big-O Runtime : O(1)
 * */
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
 * Frees all the data in the set sp passed in the argument.
 *
 * Big-O Runtime : O(n)
 * */
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
/* Function : search PRIVATE
 * Searches for character elt within set sp. Also takes in a bool.
 * Binary search used.
 *
 * Big-O Runtime : O(Log(n))
 * */
static int search(SET *sp, char *elt, bool *found)
{
    int i, lo, hi, mid;
    int flag;

    lo = 0;
    hi = sp->count-1;

    while(lo <= hi)
    {
        mid = (lo+hi)/2;
        if(strcmp(elt ,sp->data[mid]) < 0)
            hi = mid-1;
        else if(strcmp(elt, sp->data[mid]) > 0)
            lo = mid+1;
        else
        {
            *found = true;
            return mid;
        }
    }

    *found = false;
    return lo;
}
/* Function : numElements
 * Returns total number of elements in the set
 * 
 * Big-O Runtime : O(1)
 *
*/
int numElements(SET *sp)
{
    assert(sp != NULL);

    return(sp->count);
}

/* Function : addElement
 * Adds the word from the file into the set
 * The insertion is sorted
 *
 * Big-O Runtime : O(n)
 */
void addElement(SET *sp, char *elt)
{
    int i, idx;
    bool check;
    
    assert(sp != NULL);

    idx = search(sp, elt, &check);

    if(check == false)
    {
	for(i = sp->count; i > idx; i--)
	    sp->data[i] = sp->data[i-1]; //Moves all elements below idx down

	sp->data[idx] = strdup(elt); //Inserts words into index number idx
	sp->count++;
    }
    return;
}

/* Function : removeElement
 * Removes an element from the set shifts
 * to maintain the sorted set.
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

	for(i = idx+1; i < sp->count; i++) //Shifts all elements below idx upwardss
	    sp->data[i-1] = sp->data[i];

	sp->count--;
    }
    return;
}
/* Function : findElement
 * Finds an element in the set sp and returns it,
 * if the element isn't found NULL is returned.
 *
 * Big-O Runtime : O(log(n))
 *
 * */

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
/* Function : getElement
 * Creates another array which copies all the words
 * from the set.
 *
 * Big-O Runtime : O(1)
 * */
char **getElements(SET *sp)
{
    char **a;

    assert(sp != NULL);

    a = malloc(sizeof(char*)*(sp->count));

    assert(a != NULL);
    memcpy(a, sp->data, sizeof(char*)*(sp->count)); //Copies all of the words in sp into a

    return a;
}
