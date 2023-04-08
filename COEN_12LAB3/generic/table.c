#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct set
{
    int length;
    int count;
    void **data;
    char *flag;
    int (*compare)();
    unsigned (*hash)();
}SET;

SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)())
{
    SET *sp;
    int i;
    sp = malloc(sizeof(SET));

    sp->count = 0;
    sp->length = maxElts;
    sp->compare = compare;
    sp->hash = hash;
    sp->data = malloc(sizeof(char*)*maxElts);
    sp->flag = malloc(sizeof(char)*maxElts);
    

    for(i = 0; i < sp->length; i++)
	sp->flag[i] = 'E';

    assert(sp != NULL);
    return sp;
}

void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;

    for(i = 0; i < sp->length; i++)
        free(sp->data[i]);

    free(sp->data);
    free(sp->flag);
    free(sp);
}

unsigned strhash(char *s)
{
    unsigned hash = 0;

    while(*s != '\0')
        hash = 31 * hash + *s++;

    return hash;
}

static int search(SET *sp, void *elt, bool *found)
{
    int index, i, delstore;
    int head = (*sp->hash)(elt) % sp->length;
    delstore = -1;

    for(i = 0; i < sp->length; i++)
    {
	index = (head+i) % sp->length;

        if(sp->flag[index] == 'F' && (*sp->compare)(sp->data[index],elt) == 0)
        {
            *found = true;
            return index;
        }
	else if(sp->flag[index] == 'D')
	{
	    if(delstore == -1)
		delstore = index;
	}
	else
	{
	    *found = false;
	    break;
	}
    }
    if(delstore == -1)
	return index;

    return delstore;
}

int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

void addElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found);
    if(!found)
    {
	assert(sp->count < sp->length);
        sp->data[index] = elt;
        sp->flag[index] = 'F';
        sp->count++;
    }
    return;
}

void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found);
    if(found == true)
    {
        sp->flag[index] = 'D';
        sp->count--;
    }
    return;
}

void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;

    search(sp, elt, &found);
    
    if(found == true)
        return elt;
    
    else 
        return NULL;
}

void *getElements(SET *sp)
{
    assert(sp != NULL);
    char **a;
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
