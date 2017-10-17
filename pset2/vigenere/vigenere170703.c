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
            printf("Two command line arguments received.");
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
    
    
    
    
// SPEC 4 (To-Do):
    // If user passes the above checks
    // Program must proceed to prompt the user for a string of plaintext, p, 
        // (do by a prompt for plaintext:) 
    // which it must then encrypt according to Vigenère’s cipher with k, 
    // ultimately printing the result
        // (prepended with ciphertext: and ending with a newline) 
    // and exiting, with main returning 0.


// Convert the secret key into an integer
    
    // Measure the length of the keyword, to deteremine size of array.
    int keyLength = strlen(argv[1]);
    // Set size of array to lenght of keyword.
    int key[keyLength];
    
    // Loop through characters in argv[1], the keyword.
    for (int i=0, n = strlen(argv[1]); i < n; i++ ) {
        
        // Turn the i'th character of argv[1], the keyword, into an integer.
        // Store the i'th character of argv[1] into the i'th character of the key array.
        key[i] = atoi(&argv[1][i]);
    }
    
        


// Ask for plaintext (to convert into cipher text later)
    printf("plaintext: ");
    string plaintext = get_string();

// Indicate that the upcoming text will be ciphertext
    printf("ciphertext: ");

// Initialize ciphertext variable
    string ciphertext = plaintext;


// Change plaintext characters into letters that come [secret key] number of characters away
    // Iterate over each character of the plaintext, one at a time.
    for (int i = 0, j = 0, k = keyLength, lengthofPlainText = strlen(plaintext); i < lengthofPlainText; i++)
    {
    
        
        // while plaintext is not an alphabetic character,
        while (isalpha(plaintext[i]) == false) {
            
            // print the i'th character of plaintext,
            printf("%c", plaintext[i]);
            
            // then inrement i by one, to move to next character.
            i++;
        }
    
        
            // Preserve uppercase
            if ( isupper(plaintext[i]) ){
                
                // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                ciphertext[i] = ( (plaintext[i] - 65) + key[j]) %26;
                
                // Convert back from alphabetic index to ASCII index for uppercase letters
                ciphertext[i] = ciphertext[i] + 65;
            
                // Print ciphertext
                printf("%c", ciphertext[i]);
            
            
            // Preserve lowercase
            } else if (islower(plaintext[i]) ) {
            
                
                // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                ciphertext[i] = ( (plaintext[i] - 97) + key[j]) %26;
                
                // Convert back from alphabetic index to ASCII index for lowercase letters
                ciphertext[i] = ciphertext[i] + 97;
            
                // Print ciphertext
                printf("%c", ciphertext[i]);
            
            }
                
                
            if(j <= k) {
            
                j++;
                
            } else {
                j = 0;
            }
            
            
            
        
        
    }
    // Loop back to top until all the plaintext has been encrypted
    
    // Print new line at the end of ciphertext
    printf("\n");

// End main function
}
