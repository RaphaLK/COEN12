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
    char **data;
    char *flag;
}SET;

SET *createSet(int maxElts)
{
    SET *sp;
    sp = malloc(sizeof(SET));

    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    sp->flag = malloc(sizeof(char)*maxElts);
    sp->flag = 'E';

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

static int search(SET *sp, char *elt, bool *found)
{
    int index, i;

    for(i = 0; i < sp->length; i++)
    {
        index = strhash(elt);

        if(sp->flag[index] == 'F' && strcmp(sp->data[index], elt) == 0)
        {
            found = true;
            return index;
        }
        else if(sp->flag[index] == 'E')
        {
            *found = false;
            break;
        }
    }
    return NULL;
}

int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

void addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found);
    if(found == false || sp->count < sp->length)
    {
        sp->data[sp->count] = strdup(elt);
        sp->flag[index] = 'F';
        sp->count++;
    }
    return;
}

void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    bool found;
    int index;

    index = search(sp, elt, &found);
    if(found == true)
    {
        free(sp->data[index]);
        sp->flag[index] = 'D';
        sp->count--;
    }
}

char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    int i;
    bool found;

    search(sp, elt, &found);
    
    if(found = true)
        return elt;
    
    else 
        return NULL;
}

char **getElements(SET *sp)
{
    assert(sp != NULL);
    char **a;

    a = malloc(sizeof(char*)*(sp->count));
    assert(a != NULL);
    memcpy(a, sp->data, sizeof(char*)*(sp->count));

    return a;

}