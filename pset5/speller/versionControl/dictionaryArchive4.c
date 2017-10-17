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
#include <strings.h>

// Hash table size
const int HASHTABLE_SIZE = 2063;

// hashtable
node *hashtable[HASHTABLE_SIZE];


/**
 * Returns hash
 * Credit: delipity
 * Link: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
 */

int hash_it(const char* needs_hashing)
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
    // Recieve word
    // // Cast word to char * for hashing
    // char *wordPermissive = word;

    // Get element of hash table where word could be found, if it is a word, spelled correctly.
    int hash = hash_it(word);

    node *cursor = hashtable[hash];

        while (cursor != NULL)
        {
            // Check to see whether the current word from 'text'
                // matches the word in the current node
// ----
// >>>>
// ----
            if (strcasecmp(cursor->word, word) == 0)
            {
                // word is in dictionary
                return true;
            }

            // move cursor to the next node in the linked list
            cursor = cursor->next;
        }


    // word is not in the dictionary
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{

    // open the dictionary file
    FILE *dptr = fopen(dictionary, "r");

    // Check to see if we could open dictionary
    if (dptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // Create temporary storage for word in dictionary
        // Size of the longest word in the dictionary
    char bufferWord[LENGTH+1];


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

            // cast bufferWord into a constant char * (immutable string)
                // hash function has to accept const char * b/c of check(const char *word)
            const char *bufferConstant = bufferWord;

            // Run the hash function to get a node placement
            int hash = hash_it(bufferConstant);

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

    // Let speller.c know we have successfully loaded the dictionary
    return true;

    // Add something here to prevent error
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
