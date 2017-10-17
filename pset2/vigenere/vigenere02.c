// OLD VERSION OF VIGENERE





// v   v   v   Rubber Duck Talk   v   v   v
// 
// Question: How do I alter the formula for caesar to incorporate the new logic for vigenere?
    // Answer: 
    
// Question: How do I change the code to accept a word as a command line argument rather than the caesar integer?
    // Answer: Remove the atoi function
    
// Question: How do I get the program to only accept a single word command line argument with only alphabetic characters?
    // Answer: 
    
// Question: How do I get it to exit the program immediately after the error message from above? ^^^ 
    // Answer: Return value of 1
    
// Question: 


// Pseudo code (All together):

// Include libraries

// Start Main function

// Accept 2 command line arguments
    // One is the program
    // Two is the key (word)
    
// Check whether I have received a keyword with only alphabetic characters
    // If yes, print plaintext
    // If no, print error
        // Eject user from program w/ return value of 1

// Print plaintext: and ask user for word to encrypt

// Loop through each character of the word

    // Change plaintext to integer
    // Convert to alphabetic index
    
    // Loop through each character of the keyword, until the entire plaintext has been encrypted
        // Change corresponding letter of keyword into alphabetic index value (Do I need to do this?)
            // Answer: 
                // use atoi function to change letter to integer
                // Store integer in a variable
                // Change the ASCII index to alphabetic index
                
    // Use alphabetic index value in vigenere formula to encrypt corresponding plaintext letter
    
    

// Print ciphertext: and give use back the encrypted text




// Pseudo code (separated by code):


// Include libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Start Main function

// Accept 2 command line arguments
    // One is the program
    // Two is the key (word)
    
int main(int argc, string argv[])
{    
    
// Check to see if I received anything other than 2 arguments
    // & whether I have received a non-alphabetic character
    // & whether argv[1] was stored in memory correctly
    if(argc != 2 | argv[1] == NULL | isalpha(argv[1]) == false ) {
        
        // If yes, then throw error
        printf("Please provide a secret key word with only alphabetic characters\n");
        
        // exit the program
        return 1;
        
    } else {
        printf("argv[1} is %s\n", argv[1]);
    }
    // else proceed
    
    
// Get length of keyword
    string keyword = argv[1];
    
    if ( keyword != NULL) {
        printf("keyword is %s\n", keyword);
    }
    
    int lengthOfKeyword = strlen(keyword);
    printf("length of keyword is %i\n", lengthOfKeyword );
    
// Convert keyword from ASCII Index to Alphabetic Index
    for (int i = 0; i < lengthOfKeyword; i++ ) {
        
        // Preserve uppercase
        if ( isupper(keyword[i]) ){
            
            keyword[i] = keyword[i] - 65;
            
            printf("keyword[%i] is %i\n", i, keyword[i]);
            
        // Preserve lowercase
        } else if (islower(keyword[i]) ) {
            
            keyword[i] = keyword[i] - 97;
            
            printf("keyword[%i] is %i\n", i, keyword[i]);
        }
        
    }

// Print plaintext: and ask user for word to encrypt
    printf("plaintext: ");
    string plaintext = get_string();
    
    if ( plaintext != NULL) {
        printf("plaintext is %s\n", plaintext);
    }

// Initialize ciphertext variable
    string ciphertext = plaintext;
    
    if ( ciphertext != NULL) {
        printf("ciphertext is %s\n", ciphertext);
    }

// Print ciphertext:
    printf("ciphertext: ");

    // Keyword character counter
    int j = 0;

// Loop through characters in the plaintext the user wants to encrypt
    for (int i = 0, lengthofPlainText = strlen(plaintext); i < lengthofPlainText; i++)
    {
        printf("\nnow on key letter %i, which equals in Alpha-index %i\n", j , keyword[j] );
        
        // // Loop through characters in keyword
        // for (int j = 0 ; j < lengthOfKeyword ; j++){
            
            // Check to see if each character in the string is alphabetic
            if( isalpha (plaintext[i]) | ispunct(plaintext[i]) | isblank(plaintext[i]) ) {
                
                printf("recognized that plaintext[%i] is an alphabetic character\n", i );
                
                // Preserve uppercase
                if ( isupper(plaintext[i]) ){
                    
                    // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                    ciphertext[i] = ( (plaintext[i] - 65) + keyword[j]) %26;
                    
                    // Convert back from alphabetic index to ASCII index for uppercase letters
                    ciphertext[i] = ciphertext[i] + 65;
                
                    // Print ciphertext
                    // printf("%c", ciphertext[i]);
                    printf("encrypted plaintext[%i], the letter %c, to the letter %c\n", i, plaintext[i], ciphertext[i]);
                
                
                // Preserve lowercase
                } else if (islower(plaintext[i]) ) {
                
                    
                    // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                    ciphertext[i] = ( (plaintext[i] - 97) + keyword[j]) %26;
                    
                    // Convert back from alphabetic index to ASCII index for lowercase letters
                    ciphertext[i] = ciphertext[i] + 97;
                
                    // Print ciphertext
                    // printf("%c", ciphertext[i]);
                    printf("encrypted plaintext[%i], the letter %c, to the letter %c\n", i, plaintext[i], ciphertext[i]);
                
                // else print plaintext character without encryption
                }  else {
                    // printf("%c", ciphertext[i]);
                    printf("encrypted plaintext[%i], the letter %c, to the letter %c\n", i, plaintext[i], ciphertext[i]);
                    
                }
                
                // move to next letter of the keyword
                if (j<lengthOfKeyword) {
                j++;
                } else {
                    j = 0;
                }
            
                
            } 
            else {
                // Throw error message
                printf("Please only use alphabetic characters\n");
                return 1;
            }    
        
        // }
                
    }

    // Print new line at the end of ciphertext
    printf("\n");
    return 0;
    
// End main
}    
    