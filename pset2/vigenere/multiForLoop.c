// Include libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Error identification and diagnoses
    int keyLen = strlen(key);
    
    for(i=0; i<keyLen; i++) {
        if (isalpha(keyword[i]) == false) {
            printf("Only use alphabetic characters or spaces in your key");
            return 1;
        }  
        // this is a word, phrase, or sentence
        // therefore, continue
    }


// Convert key from ASCII to Alphabetic Index
    for(i=0; i<keyLen; i++) {
       if (isupper(key[i])) {
            key[i] = key[i] - 65;
        } 
        else if (islower(key[i])) {
            key[i] = key[i] - 97;
        } else {
            // this is a space
            // therefore, continue    
        }
        
    }
    
// Prompt the user for a string of plaintext, p, (as by a prompt for plaintext:) 
    printf("plaintext: ")
    string plaintext = GetString();
    
// Convert plaintext from ASCII to Alphabetic Index. Save alphabetic characters to variable.
    int plaintextLen = strlen(plaintext);
    string alphaPlaintext = plaintext;
    
    for(i=0; i<plaintextLen; i++) {
       if (isupper(plaintext[i])) {
            alphaPlaintext[i] = plaintext[i] - 65;
        } 
        else if (islower(plaintext[i])) {
            alphaPlaintext[i] = plaintext[i] - 97;
        } else 
        // this is non-alpha
        // therefore, do not save to alphaPlaintext (i.e. skip)
    }


// Encrypt (try 2): Only alphabetic characters
    string ciphertext = plaintext;
    
    for(i = 0; i<strlen(alphaPlaintext); i++){
        for(j = 0; j <= i%strlen(keyword); j++){
            ciphertext[i] = (alphaPlaintext[i] + keyword[j]) %26
        }
    }

// // Encrypt (try 1)
//     string ciphertext = plaintext;
//     keyCount = 0;

//     for(i=0; i<plaintextLen; i++){
//         if (isalpha(plaintext[i])) {
//             ciphertext[i] = (plaintext[i] + key[i]) %26;
//             keyCount = (keyCount+1)%(keyLen);
//         } else 
//         // is a space
//         // continue
            
//     }

// convert back to ASCII    
    int ciphertextLen = strlen(ciphertext);
    
    for(i=0; i<plaintextLen; i++) {
        
        
        plaintext: a9p1e5
        alphaPlain: ape
                    1224    
        ciphertext: b9p1x
                        ^
                        null
                        
        // How is it going to recongize if it is upper, when the characters are in an alphabetic index, not an ASCII? 
            // Question 1.1: I am going to have to convert back to ASCII in the earlier for loops with the isupper and islower boolean statements.
                // Answer: No. Instead, I could convert based on the ASCII value. I know that any number 65 of lower is going to be... no nevermind that will not work because the number are all going to be 0-26.
                // Answer 2.0: Instead, convert plaintext to ASCII, but store it in a different variable than the original plaintext variable. Keep the plaintext variable as is, then use it to identify whether something should be upper or lower case when we convert back. 
            // Question: Still have to figure out how to skip non-alpha characters.
                // Note:i is going to have to increase over a space, but j has to stay the same as if there were no space.
                // Note: Could I remove spaces and non-alpha characters from the string, encrypt, then add them back?
                // Note: Yes, I could. I could remove (not save) the non-alpha characters in the alphabetized plaintext variable. That would mean the alphaPlaintext variable only had alpha characters in it
                    // Then when I use isupper/lower functions on the original plaintext, I can print any character that is above ASCII=26 in the plaintext. 
                    // I would first check if ASCII =! [alphabetic ASCII values], if yes, then I would print. 
                    // Then I could move onto the next values in the plaintext, to determine if I want to convert those encrypted characters back to ASCII and print.
                    // Note Note: That would work for printing the plaintext characters that were not alpha, but how would the program know to not skip the corresponding ciphertext character.
                    // Answer to Note Note: I would have to print the plaintext character first, followed by the ciphertext character of the same i'th placeholder 
                        // (E.g. if plaintext[i] is non-alpha, print that, but then print the ciphertext[i] within the same boolean statement.)
                        // That way you get the correct ciphertext character after the plaintext character, and can move onto the next i.
                        // I would have to 
        if(isupper())
    }