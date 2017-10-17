    // v  v  v  Rubber duck talk  v  v  v
    
        //how do you get the character that comes after a space?
        //what if I went backwards and set the loop to iterate until the character equalled a space
        //or what if I incremented until 1 character after a character that equalled space
        //
    
    
    // Iterate until i-1 equals a " " i.e. the space charcter
    // Iterate until i+1 equals a " " i.e. the space charcter? (no use i-1)
    // then printf name[i]
    // 
    // Question: Next, how do I get it to loop through the entire string to look for those three characters?
        //Answer: Put a loop inside another loop. Big loop will loop while i<strlen. Then inner loop will loop until a space character is hit.
        // Question: Will this cause the function to print out the first initial over and over?
            // Answer: Maybe, but probably not. 
            // Make sure the the value of i is retained from loop to loop so that it starts from where it left off. 
            // Reset the value of i to zero at the end of the program. 
            // This might not be necessary if the start of the function sets i to equal zero. Which it does.
            // 
            // Note: Need to print out the first character always b/c there will not be a space character before the first initial.
     
     
            
// Pseudo code (all together)
    // 
    // Set up program (i.e. libraries)

    // create name variable 

    //start main function    

    // get string from user
    // store string from user in variable name

    // Loop through name

    // print first letter as the first initial (i.e. print character)

            
    // loop through string until it comes to a space character 

    // exit "while" loop
    // go back to the top of the "for" loop
    // check to see if i is less than string length 
    // increase i by 1
    // print the i character of the name array
    // re-enter loop until next space character
    
    //end of "for" loop that goes through "name" variable
    
    //end of main function bracket

    
    
    
    
    
// Pseudo code (seperated by actual code)
    // 
    // Set up program (i.e. libraries)
        #include <stdio.h>
        #include <cs50.h>
        #include <math.h>
        #include <string.h>
        #include <stdlib.h>
        #include <ctype.h>

            

    // create name variable 
        string name;
        
    //start main function    
        int main (void)
        {
            
        
    // get string from user
    // store string from user in variable name
            name = get_string();
        
        
    // Loop through name
            for (int i = 0; i < strlen(name); i++)
            {
                
    // print first letter, in uppercase, as the first initial (i.e. print character)
                printf("%c", toupper(name[i]));
            
            
    // loop through string until it comes to a space character 
    // Process received SIGSEGV: Segmentation fault! Why?
                while isalpha(name[i])
                {
                    i++;
                };
    
    //
    // exit "while" loop
    // go back to the top of the "for" loop
    // check to see if i is less than string length 
    // increase i by 1
    // print the i character of the name array
    // re-enter loop until next space character
    //
    
    
    //end of "for" loop that goes through "name" variable
            } ;
            
            
    // Print new line, per CS50 instructions
            printf("\n");
            
    //end of main function bracket
        }   ;
    

