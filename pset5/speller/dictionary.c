/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>
#include <cs50.h>

// Hash table size
const int HASHTABLE_SIZE = 307;
// const int HASHTABLE_SIZE = 3;

// Pointer to keep track of our hashtable later on
node *hashtable[HASHTABLE_SIZE];

void clear_hashtable(void) {

    for (int i = 0; i < HASHTABLE_SIZE; i++) {

            hashtable[i] = NULL;
    }
}


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

    // Allocate memory for lowercase word
    // The input word needs to be lowercase, same as the dictionary word.
    // Otherwise the hash code will not match. The hash function is case sensitive.
    char *textWord = malloc(strlen(word) + 1);
    if (textWord == NULL) {
        unload();
        return false;
    }

    strcpy(textWord, word);

    // Convert to lowercase
    for (int i = 0, n = strlen(textWord); i < n; i++){
        if (isupper(textWord[i]))
            textWord[i] = tolower(textWord[i]);
    }


    // Get element of hash table where word might be found.
    int hash = hash_it(textWord);

    // Set cursor to the hashtable[hash] of the linked list
        // where the word would most likely be found
    node *cursor = hashtable[hash];

    while (cursor != NULL)
    {

        // if word matches a word in the dictionary
        if ((strcasecmp(cursor->wordValue, textWord)) == 0)
        {
            // word is in dictionary
            free(textWord);
            return true;
        }
        // if word does not match the current word in the ditionary,
            // but there are still words left to check
            // move cursor to the next word in the dictionary
            cursor = cursor->next;

    }

    // word is not in the dictionary
    free(textWord);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{

    // Prepare the hashtable by initalizing it to have NULL values and pointers
    clear_hashtable();

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

    // printf("\nWORDS IN DICTIONARY\n");

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
            strcpy(new_node->wordValue, bufferConstant);
            // printf("dictionary.c:~168 %s\n", new_node->wordValue);


            // if this is the first item in a linked list
            if (hashtable[hash] == NULL) {

                // Set hashtable[hash] to point to new_node
                new_node->next = NULL;
                hashtable[hash] = new_node;

            }

            // else if there is already a linked list within this element of the hashtable
            else if (hashtable[hash] != NULL) {

                node *head = new_node;
                new_node->next = hashtable[hash];
                hashtable[hash] = head;


                // // Set the pointer of the new_node to the first node in the linked list
                // new_node->next = hashtable[hash];

                // // Point hashtable[hash], the head of the linked list, to the new_node
                // hashtable[hash] = new_node;

            }

            // prepare for next word
            index = 0;
        }

    }

    printf("\n");
    fclose(dptr);
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
    // Create variable to count the number of words
    int ctr = 0;

    // Look at each element in the hashtable
    for (int i = 0, n = HASHTABLE_SIZE; i < n; i++ ) {

        // Track place in dictionary
        node *cursor = hashtable[i];

        // Read the value in the linked list
        while (cursor != NULL) {

            // Add one to the word counter
            ctr++;

            // move onto the next object in the list
            cursor = cursor->next;

        // repeat until end of linked list
        }
    // repeat until end of the hash table
    }

    // return the number of words
    return ctr;

    // return 0 if something goes wrong
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{

    // // Staff's Code
    // node *cursor = head; //note that head needs to be named something different, based on our specific code.

    // while (cursor != NULL) {

    //     node *temp = cursor;
    //     cursor = cursor->next;
    //     free(temp);

    // }



    // My solution based on staff's

    // int i = 0;



    // while (i <= HASHTABLE_SIZE) {

    //     node *head = hashtable[i];

    //     while (head != NULL) {

    //         node *cursor = head;

    //         node *temp = cursor;
    //         cursor = cursor->next;
    //         free(temp);

    //     }

    //     i++;

    // }


    // ATTEMPT 1

    // Loop through elements of table
    for (int i = 0, n = HASHTABLE_SIZE; i < n; i++) {

        // Track head of list
        node *head = hashtable[i];

        // while there are nodes in the element
        while (head != NULL) {

            node *temp = head->next;
            free(head);
            head = temp;

        }

    }

    return true;
    // else
    return false;
}
