
// v   v   v   Rubber Duck Talk   v   v   v
// 
// Question: How do we accept command line arguments?
//  Answer: With argc and argv in the main function
// 
// Question: How will we turn the secret key into an int?
//  Answer: With the atoi() function 
// 
// Question: How will we turn any int into a value of 1-26? (the remainder of a number divided by 26?)
//   Answer: Use the C modulo operator. Combine with the ASCII table.
// 
// Question: How will I get the letters to loop through only their section of the ASCII Table?
//  Answer: related to c = (p + k) mod 26. Not sure how to use this algorithm in the code though. 
    // Maybe I need to learn more about the ASCII table and how numbers can be added to letters to change their value. 
    // (e.g. do I add 1 to a and it comes out as b?)
// 
// Question: Does returning a value of 1 to the main function autogenerate an error message?
//  Question: What is the significance of returning 1? 
//  Question: Do I use that to generate the error message in my own code?
//      Answer:


// Question: How do I preserve the case of the letter?
    // Question: When I have the letter z and a key of 2, how do I go from ASCII z = 122 back to b = 98?
    // Answer: 



// Pseudo code (separated by code)

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
    


// 
// Check to see if I received anything other than 2 arguments
//  If yes, then throw error
    if(argc != 2) {
        printf("Please provide a secret key\n");
    // exit the program
        return 1;
    } 
    // else proceed
    

// Set variable "key" to be the secret key
// Convert the secret key into an integer
    int key = atoi(argv[1]);


// Ask for plaintext (to convert into cipher text later)
    printf("plaintext: ");
    string plaintext = get_string();

// Indicate that the upcoming text will be ciphertext
    printf("ciphertext: ");

// Change plaintext characters into letters that come [secret key] number of characters away
    // Iterate over each character of the plaintext, one at a time.
    for (int i = 0, lengthofPlainText = strlen(plaintext); i < lengthofPlainText; i++)
    {
    
        // Check to see if each character in the string is alphabetic
        if( isalpha (plaintext[i]) | ispunct(plaintext[i]) | isblank(plaintext[i]) ) {
        
        // Initialize cipher text variable
        string ciphertext = plaintext;
    
            // Preserve uppercase
            if ( isupper(plaintext[i]) ){
                
                // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                ciphertext[i] = ( (plaintext[i] - 65) + key) %26;
                
                // Convert back from alphabetic index to ASCII index for uppercase letters
                ciphertext[i] = ciphertext[i] + 65;
            
                // Print ciphertext
                printf("%c", ciphertext[i]);
            
            
            // Preserve lowercase
            } else if (islower(plaintext[i]) ) {
            
                
                // Convert letter to cipher text, after conversion from ASCII to alphabetic index.
                ciphertext[i] = ( (plaintext[i] - 97) + key) %26;
                
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
        
            
        } else {
            // Throw error message
            printf("Please only use alphabetic characters\n");
            
            // re-prompt user for string
            plaintext = get_string();
            
            // reset i to zero to restart scan through text
            i = 0;
        }
        
    }
    // Loop back to top until all the plaintext has been encrypted
    
    // Print new line at the end of ciphertext
    printf("\n");

// End main function
}
