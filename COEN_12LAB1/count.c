//Raphael Kusuma
//LAB 1 - COEN12L
//5:15pm - 8:00pm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char* argv[])
{
    int counter = 0;
    FILE *infp;
    char word[MAX_WORD_LENGTH];

    if(argc != 2) //Checks for number of arguments
    {
        printf("Not enough arguments\n\n");
        return 0;
    }

    infp = fopen(argv[1], "r"); //Opens up text file in argument line

    if(infp == NULL)
    {
        printf("Can't open the file\n\n");
        return 0;
    }    

    while(fscanf(infp, "%s", word) == 1) //Checks for number of words
        counter++;

    printf("There are %d words\n\n", counter);

}
