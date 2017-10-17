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
const int HASHTABLE_SIZE = 307;

// Pointer to keep track of our hashtable later on
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

    // Get element of hash table where word might be found.
    // int hash = hash_it(word);

    // Set cursor to the head of the linked list
        // where the word would most likely be found
    node *cursor = hashtable[hash_it(word)];

    // // Error Check: make sure hashtable[hash] has a word in it.
    // printf("%s", cursor->word);

    // // Skip over the head node
    // cursor = cursor->next;

    // // Error Check: make sure we moved onto the next node.
    // printf("%s", cursor->word);

        while (cursor->next != NULL)
        {
            // Check to see whether the current word from 'text'
                // matches the word in the current node
// ----
// >>>>
// ----
            // if word matches a word in the dictionary
            if ((strcasecmp(cursor->word, word)) == 0)
            {
                // word is in dictionary
                free(cursor);
                return true;
            }
            // if word does not match the current word in the ditionary,
                // but there are still words left to check
            else if ((strcasecmp(cursor->word, word)) != 0 ) {

                // move cursor to the next word in the dictionary
                cursor = cursor->next;
            }

            // if word does not match the current word in the ditionary,
                // and there are no more words in the dictionary
            else if ((strcasecmp(cursor->word, word)) != 0){
                free(cursor);
                return false;
            }
        }

    free(cursor);
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
        // Size = longest word + string terminate character '\0'
    char bufferWord[LENGTH+1];


    // prepare to load each word
    int index = 0, words = 0;

    // Load each word in the dictionary
    // Loop through each character in the dictionary, until end of file is reached.
    for (int c = fgetc(dptr); c != EOF; c = fgetc(dptr))
    {

        // Check to see if letter or apostrophe
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            bufferWord[index] = c;
            // keep track of which array element to place the next character.
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
                    // We cannot start with const char *bufferWord because
                    // then we would not be able to change the characters
            const char *bufferConstant = bufferWord;

            // Run the hash function to get a node placement
            int hash = hash_it(bufferConstant);

            // Create a node *new_node for linked list
            node *new_node = malloc(sizeof(node));
            // Make sure we did not run out of memory.
            if (new_node == NULL)
            {
                unload();
                return false;
            }

            // set the new_node's word value to be the bufferWord
            strcpy(new_node->word, bufferWord);

            // // Create a head pointer to save our location.
            // node *head = malloc(sizeof(node));

            //     // Make sure we did not run out of memory.
            //     if (head == NULL)
            //     {
            //         unload();
            //         return false;
            //     }



            // if this is the first item in a linked list
            if (hashtable[hash] == NULL) {

                // Assign the pointer in new_node to NULL,
                    // b/c there will be no items after new_node in the linked list.
                new_node->next = NULL;

                // Set head to point to new_node
                hashtable[hash] = new_node;

                    // Check to make sure we indeed created a linked list.
                    if (hashtable[hash] == NULL) {
                        return false;
                    }



            }

            // else if there is already a linked list within this element of the hashtable
            else if (hashtable[hash] != NULL) {

                // Set the pointer of the new_node to the first node in the linked list
                new_node->next = hashtable[hash];

                    // Check to make sure new_node's next pointe was set
                    if (new_node->next == NULL) {
                        return false;
                    }

                // Move the head pointer to point to the new_node
                hashtable[hash]->next = new_node;

                    // Check to make sure we indeed created a linked list.
                    if (hashtable[hash] == NULL) {
                        return false;
                    }

                // Ensure the last object in the linked list points to NULL.
                    // This will happen by default, because we always insert at the beginning of the linked list.
                    // Whatever node was at the end to begin with, will stay at the end.
                    // This only needs to be implemented, if we were ever to insert a node at the end of the linked list.

            }

            // prepare for next word
            index = 0;
            free(new_node);
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
