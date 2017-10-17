/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO

    // open the dictionary file
    FILE *dtyptr = fopen(dictionary, "r");

    // Check to see if we could open dictionary
    if (dtyptr == NULL) {
        fprintf(stderr, "Could not open file");
        return false;
    }

    // Temporary memory size of the longest possible word
    char * dtyWord = malloc(LENGTH + 1);


    // Write loop to store characters of a word into dtyWord
    for (int i = 0, dtySize = sizeof(dictionary); i <= dtySize; i++) {

        // if dtyptr does not equal \n, then we have not reached end of word
        if (strcmp(dtyptr,"\n") != 0) {

            fread(dtyWord, sizeof(char), 1, dtyptr);

        } else if (strcmp(dtyptr,"\n") == 0) {

            // check for correctness
            printf("%s @dtyptr[%i]\n", dtyWord, ftell(dtyptr));

        } else {
            fprintf(stderr, "Found a weird character in dictionary");
            return false;
        }

    // }
    // /*
    //     Load dictionary into a hash table
    //     Credit: Dan Bernstein, djb2
    //     Link: http://www.cse.yorku.ca/~oz/hash.html
    // */
    // unsigned long hash(unsigned char *str)
    // {
    //     unsigned long hash = 5381;
    //     int c;

    //     while (c = *str++)
    //         hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    //     return hash;
    // }





    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
