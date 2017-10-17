// CS50x 2017 VERSION

// Last Updated: 170731


// Rubber Duck Talk

// When I "Convert the secret key into an integer", 
    // will int key[i], be in an organized array? 
    // Does it need to be in order for me to make use of it?


// Pseudo code (separated by code)

// SPEC 1 (COMPLETE): A file called vigenere.c in a directory called vigenere.


// Include libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Start main fuction
//  Accept 2 arguments
//      The "start program" command
//      The secret key
int main(int argc, string argv[])
{
    


    // SPEC 2 (COMPLETE): Accept a single command-line argument: a keyword, k, composed entirely of alphabetical characters
        if(argc == 2) {
            printf("Two command line arguments received.\n\n");
        } 
        
        
    // SPEC 3.1 (COMPLETE):
        // If your program is executed without any command-line arguments 
        // or with more than one command-line argument, 
       
        else if(argc != 2) {
            printf("Usage: ./vigenere k\n");
        // exit the program
            return 1;
        } 
       
        
    // SPEC 3.2 (COMPLETE):
        // If your program is executed with one command-line argument that contains any non-alphabetical character
        // your program should print an error (of your choice) and 
        // exit immediately, with main returning 1 (thereby signifying an error).
        
        // Check whether argv[1], the second command-line argument, is an alphabetic character. 
        // If it is not (i.e. if isalpha returns "false"), 
        else if (isalpha(argv[1]) == false) {
            
            // Then print an error.
            printf("keyword contains a non-alphabetic charater. Please try again with only alphabetic characters.\n");
            
            // and exit the program immediately
            return 1;
        }
    
    
    
    
// SPEC 4.1 (Complete):
    // If user passes the above checks
    // Program must proceed to prompt the user for a string of plaintext, p, 
        // (do by a prompt for plaintext:) 
        
    // Ask for plaintext
    printf("plaintext: ");
    string plaintext = get_string();
    
    // Success Confirmation
    printf("\nPlaintext '%s' received\n\n", plaintext);
        


// SPEC 4.2 (To-Do):
    // encrypt plaintext according to Vigenère’s cipher with k, 
    // ultimately printing the result
        // (prepended with ciphertext: and ending with a newline) 
    // and exiting, with main returning 0.

        
    // // Set variable "k" to be the argv[1], the secret key.
    //     string k = argv[1];
        
        // remind user what their secret key is
        printf("keyword = '");
        
        // print the secret key character by character
        for(int i=0, n = strlen(argv[1]); i < n; i++){
                printf("%c", argv[1][i]);
            
                
        }
    
        // end with a new line
        printf("'\n");
        
        
    // Convert the secret key into an integer   

       
        // Create array to store integer values of keyword
        int k[100] = {};
        
        // Loop through each character in the secret key.
        // Stop when you have looped through the length of the key
        for(int i=0, n = strlen(argv[1]); i < n; i++){
           
                // Convert i'th character argv[1] string into an integer. 
                // Store in i'th position of array 'k[]'.
                k[i] = argv[1][i];
            
                // // Print i'th integer of k[i] as an integer and character to ensure conversion worked. 
                // printf("argv[1][%i] = %i = %c --VS-- k[%i] = %i\n", i, argv[1][i], argv[1][i], i, k[i]);
           
        }
        
        
        
        
        
// Program works up until here
// ======================================================================
        
        
        
        
// SPEC 4.2 cont'd (To-Do):================================================================================================================
    // encrypt plaintext according to Vigenère’s cipher with k, 
    // ultimately printing the result
        // (prepended with ciphertext: and ending with a newline) 
    // and exiting, with main returning 0.    
    
    
    // With respect to the characters in k, you must treat A and a as 0, B and b as 1, … , and Z and z as 25.
    
    // Your program must only apply Vigenère’s cipher to a character in p if that character is a letter. 
    // All other characters (numbers, symbols, spaces, punctuation marks, etc.) must be outputted unchanged. 
    // Moreover, if your code is about to apply the jth character of k to the ith character of p, 
        // but the latter proves to be a non-alphabetical character, 
        // you must wait to apply that jth character of k to the next alphabetical character in p; 
        // you must not yet advance to the next character in k.
    
    // Your program must preserve the case of each letter in p.
    
    // ====================================================================================================================================
        
    // Indicate that the upcoming text will be ciphertext
        printf("ciphertext: ");

    // Convert k from ASCII to alphabetic index. No check for anything other than alpha, because we checked for alpha above.
        for (int i = 0, kLen = strlen(argv[1]); i < kLen; i++) {
            
            if (isupper(k[i])) {
                        k[i] = k[i] - 65;
                    } else 
                        k[i] = k[i] - 97;
        }            
                    
    
    // Change plaintext characters into letters that come [secret key] number of characters away
        // Iterate over each character of the plaintext, one at a time.
        for (int i = 0, j = 0, pLen = strlen(plaintext), kLen = strlen(argv[1]); i < pLen; i++, j++)
        {
        
            
            // Check to see if each character in the string is alphabetic
            if( isalpha (plaintext[i]) ) {
            
            // Initialize cipher text variable
            string ciphertext = plaintext;
        
                // Preserve uppercase
                if ( isupper(plaintext[i]) ){
                    
                    
                    // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                    ciphertext[i] = ( (plaintext[i] - 65) + (k[j%kLen])) %26;
                    
                    // Convert back from alphabetic index to ASCII index for uppercase letters
                    ciphertext[i] = ciphertext[i] + 65;
                
                    // Print ciphertext
                    printf("%c", ciphertext[i]);
                
                
                // Preserve lowercase
                } else if (islower(plaintext[i]) ) {
                
                    
                    // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                    ciphertext[i] = ( (plaintext[i] - 97) + (k[j%kLen])) %26;
                    
                    // Convert back from alphabetic index to ASCII index for lowercase letters
                    ciphertext[i] = ciphertext[i] + 97;
                
                    // Print ciphertext
                    printf("%c", ciphertext[i]);
                
                // else print plaintext character without encryption
                }  else {
                    printf("%c", plaintext[i]);
                }
                    
            // // Print ciphertext
            // printf("%c", ciphertext[i]);
            
                
            } else if (ispunct(plaintext[i]) | isblank(plaintext[i])) {
                
                printf("%c", plaintext[i]);
                
                j--;
                
                
            } else if (isdigit(plaintext[i])) {
                
                printf("%c", plaintext[i]);
                
                j--;
                
            }
                
    
            
            // THROW AWAY CODE - REDUNDANT
            // else {
            //     // Throw error message
            //     printf("Please only use alphabetic characters\n");
                
            //     // re-prompt user for string
            //     plaintext = get_string();
                
            //     // reset i to zero to restart scan through text
            //     i = 0;
            // }
            
        }
        // Loop back to top until all the plaintext has been encrypted
        
        // Print new line at the end of ciphertext
        printf("\n");


// End main function
}
