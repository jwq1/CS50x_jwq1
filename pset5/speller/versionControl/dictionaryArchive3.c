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
#include <ctype.h>

// Hash table size
const int HASHTABLE_SIZE = 2063;

// hashtable
node *hashtable[HASHTABLE_SIZE];


/**
 * Returns hash
 * Credit: delipity
 * Link: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
 */

int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}

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
    FILE *dptr = fopen(dictionary, "r");

    // Check to see if we could open dictionary
    if (dptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    //Create new node for word in dictionary
    // Temporary memory size of the longest possible word
    char bufferWord[LENGTH+1];

    // // Node version
    // node *bufferWord = malloc(sizeof(node));


    // prepare to load each word
    int index = 0, words = 0;

    // Load each word in the dictionary
    for (int c = fgetc(dptr); c != EOF; c = fgetc(dptr))
    {

        // Check to see if letter or apostrophe
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            bufferWord[index] = c;
            index++;

        }

        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            bufferWord[index] = '\0';

            // update counter
            words++;

            // Run the hash function to get a node placement
            int hash = hash_it(bufferWord);

            // Create a node *nodeWord and store 'bufferWord' there
            node *new_node = malloc(sizeof(node));

            // Make sure we did not run out of memory.
            if (new_node == NULL)
            {
                unload();
                return false;
            }

            // add bufferWord to 'word' value in new_node
            strcpy(new_node->word, bufferWord);

                // Assign the pointer in nodeWord to the first node in the relevant hash list.
                node *head = hashtable[hash];
                new_node->next = head;

                // Shift the head pointer to point to the nodeWord we created.
                head = new_node;


            // prepare for next word
            index = 0;
        }

    }

    return true;






    // SAVE WORD FROM DICTIONARY:
    // Loop through each character in a particular word. Stop when you find a line break.
    // for loop, with a != "\n" conditional

        // Store the character from dptr into buffer (type char*).
        // file read function by character size_t = sizeof(char), element = 1
        // Do I need to use i here to indicate the element in temporary storage array to use?
            // Probably, yes.

    // STORE WORD IN HASH TABLE:
    // Put the word into a node in the hash table

        // // Create a new node. Make size equal to length of the word
        // node *word = malloc(strlen(bufferWord));
        //     // Make sure we did not run out of memory
        //     if (word == NULL) {
        //         fprintf(stderr, "Ran out of storage");
        //         return false;
        //     }

        // declare length of word as strlen(bufferWord) to get the amount of information to store in the node

        // dynamically allocate the proper amount of memory to that node

            // store word into that new node

        // get the hash number where the new node should be stored

            // If there is already a node in that area of the hash table,
                // point the new node to the first node in particular hash
            // If there are no previous nodes in that hash table,
                // point the new node to NULL

        // point the head node to the new node




    // }
    // /*
    //     hash function: spell checker
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
