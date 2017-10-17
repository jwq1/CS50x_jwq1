/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

    // open the dictionary file
    FILE *dtyptr = fopen(dictionary, "r");

    // Check to see if we could open dictionary
    if (dtyptr == NULL) {
        fprintf(stderr, "Could not open file");
        return false;
    }

    // Temporary memory
    char * dtyWord = malloc(LENGTH + 1);

    // Write loop to store characters of a word into dtyWord
    for (int i = 0, dtySize = sizeof(dictionary); i <= dtySize; i++) {

        // if dtyptr does not equal \n, then we have not reached end of word
        if (dtyptr != \n) {

            fread(dtyWord, sizeof(char), 1, dtyptr);

        } else if (dtyptr == \n) {



            // check for correctness
            printf("%s @dtyptr[%i]\n", dtyWord, ftell(dtyptr));

        } else {
            fprintf(stderr, "Found a weird character in dictionary");
            return false;
        }

    }
    /*
        Load dictionary into a hash table
        Credit: Dan Bernstein, djb2
        Link: http://www.cse.yorku.ca/~oz/hash.html
    */
    unsigned long hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
