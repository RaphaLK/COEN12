//Raphael Kusuma
//COEN 12L - Lab 5 Part 2
//5:15-8:00PM R

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h> //Recommended by Mr. Noah Tall
#include "pack.h"
#include "pqueue.h"

/* File Summary :   
 * This file utilizes huffman coding as a method of file compression
 * By using the number of occurences of letters in a text file, we 
 * can use a priority queue to build a huffman tree.
 */
typedef struct node NODE;


//Makes a node
//
//Runtime : O(1)
static NODE* mknode(int data, NODE *left_node, NODE *right_node)
{
    NODE *p;
    p = malloc(sizeof(NODE));
    p -> count = data;
    p -> parent = NULL;

    if(left_node != NULL)
	left_node -> parent = p;
    if(right_node != NULL)
	right_node -> parent = p;
    
    return p;
}

//Private function for depth of the tree
//
//We start from the bottom of the tree and 
//count the way up to the root.
//
//Runtime : O(n)
static int depth(NODE *p)
{
    int depth = 0;
    while(p -> parent != NULL)
    {
	p = p -> parent;
	depth++;
    }
    return depth;
}

//Compare Function
//Runtime : O(1)

int compare(NODE *t1, NODE *t2)
{
    return (t1->count < t2->count) ? -1 : (t1->count > t2->count);
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r"); //Open file taken as argument and read
    int i, c;

    if(fp == NULL) //If the file is empty
    {
	printf("File Error\n");
	return 0;
    }

    int counts[257] = {0}; //Create an integer array to store the occurences for the characters.
    
    NODE *nodes[257] = {0}; //Creating another array, but an array of nodes

    for(i = 0; i < 257; i++)
	nodes[i] = NULL; //Setting all nodes to NULL first.

    //Get the characters
    while(1) //Forever Loop
    {
	c = fgetc(fp);

	if(feof(fp)) //If it reaches the end of the file, break the loop
	    break;

	counts[c]++; //Increment the counts array depending on the character read
    }
    
    //Huffman Step 3
    PQ *pq = createQueue(compare); //Creates a priority queue

    for(i = 0; i < 256; i++) 
    {
	if(counts[i] > 0)
	{
	    NODE *c = mknode(counts[i], NULL, NULL);
	    addEntry(pq,c); //Adding node c to the pqueue
	    nodes[i] = c;
	}
    }

    //Extra node for EOF with a 0 count
    NODE *eof = mknode(0, NULL, NULL);
    addEntry(pq,eof);
    nodes[256] = eof;

    //Huffman Step 4
    while(numEntries(pq) > 1)
    {
	NODE *first = removeEntry(pq); //Removing first
	NODE *second = removeEntry(pq); //Removing Second

	NODE *sum = mknode(first->count+second->count, first, second);//New one with the sum of the first two trees

	addEntry(pq, sum); //Putting the tree back in the pqueue
    }

    //Huffman Step 5
    for(i = 0; i < 257; i++)
    {
	if(nodes[i] != NULL)
	{   
	    if(isprint(i))
		printf("'%c' : %d x %d bits = %d bits\n", i, counts[i], depth(nodes[i]), counts[i]*depth(nodes[i]));
	    else
	        printf("%03o: %d x %d bits = %d bits\n",i, counts[i], depth(nodes[i]), counts[i]*depth(nodes[i]));		
	}
    }	
	
    //Huffman Step 6
    pack(argv[1], argv[2], nodes);

}

