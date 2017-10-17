// Include libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Start main function. Get arguments from user (i.e. the key).
int main(int argc, string argv[]) {

// ensure two command line arguments
    if(argc == 2) {
        printf("CONFIRMED: Two command line arguments received.\n");
    } else if (argc > 2) {
        printf("Don't be so argumentative.\n");
        return 1;
    } else {
        printf("Be a little more argumentative.\n");
        return 1;
    }
    
// assign argv[1] to key variable for legibility
    string key = argv[1];
    
// assign length of key to a variable for debugger
    int keyLen = strlen(key);
    
// convert key to alphabetic index
    for (int i = 0; i < keyLen; i++) {
        if (isupper(key[i])) {
            key[i] = key[i] - 65;
            printf("%i\n", key[i]);
        } 
        else if (islower(key[i])) {
            key[i] = key[i] - 97;
            printf("%i\n", key[i]);
        } 
        else {
            printf("Please try again with a alphabetic keyword.\nProgram end.\n");
            return 1;
        }
    }
   
// Get plaintext
    printf("plaintext: ");
    string plaintext = get_string();

// Create an array of character to convert for ciphertext
    string ciphertext = plaintext;
    string plaintextAlpha = plaintext;

// initialize keyCounter
    int keyCounter = 0;

// Loop through plaintext
    for(int i=0; i<strlen(plaintext); i++) {
        
        

    // if is not alpha
        if (isalpha(plaintext[i]) == false) {
        
        // print error message. exit w/ return 1.
            printf("not alpha character\n");
            return 1;
        }


    // else if space, 
        else if (isspace(plaintext[i])) {
        
        // 0) add 1 to variable.
            i++;
        
        // if is not alpha (again)
            if (isalpha(plaintext[i]) == false) {
        
        // print error message. exit w/ return 1.
            printf("not alpha character\n");
            return 1;
            } 
        
        // 1) change plaintext ASCII value to Alphabetic Index
            else if (isupper(plaintext[i]) == true) {
                plaintextAlpha[i] = plaintext[i] - 65;
        
        // 3a) Encrypt by key letter (mod length of key)
            ciphertext[i] = (plaintextAlpha[i] + key[i]) %26;
            
        // 4a) Change ciphertext back to ASCII value
            ciphertext[i] = ciphertext[i] + 65;
            
        // 5a) print letter
            printf("%c", ciphertext[i]);
            } 
            
            else if (islower(plaintext[i]) == true) {
                plaintextAlpha[i] = plaintext[i] - 97;
        
        // 3) Encrypt by key letter (mod length of key)
            ciphertext[i] = (plaintextAlpha[i] + key[i]) %26;
            
        // 4) Change ciphertext back to ASCII value
            ciphertext[i] = ciphertext[i] + 97;
            
        // 5) print letter
            printf("%c", ciphertext[i]);
            } 
            
            else {
                printf("I did not account for this edge case. 404!");
            }

        } 
     
     // Else is alphabetic character
         else {
            
        // 1) change plaintext ASCII value to Alphabetic Index
            if (isupper(plaintext[i])) {
                plaintextAlpha[i] = plaintext[i] - 65;
        
        // 3a) Encrypt by key letter (mod length of key)
            ciphertext[i] = (plaintextAlpha[i] + key[i]) %26;
            
        // 4a) Change ciphertext back to ASCII value
            ciphertext[i] = ciphertext[i] + 65;
            
        // 5a) print letter
            printf("%c", ciphertext[i]);
            } 
            
            else if (islower(plaintext[i])) {
                plaintextAlpha[i] = plaintext[i] - 97;
        
        // 3) Encrypt by key letter (mod length of key)
            ciphertext[i] = (plaintextAlpha[i] + key[i]) %26;
            
        // 4) Change ciphertext back to ASCII value
            ciphertext[i] = ciphertext[i] + 97;
            
        // 5) print letter
            printf("%c", ciphertext[i]);
            } 
            
            else {
                printf("I did not account for this edge case. 404!");
            }
        }

    // Increment keyCounter within the length of the key.
        keyCounter = (keyCounter+1)%(keyLen);

    }

  return 0;  
}



