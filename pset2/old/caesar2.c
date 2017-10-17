#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
 
int main (int argc, string argv[])
{
 
    //make sure user enters key
    if (argc != 2)
       {
            printf("try again...program is quitting...");
            return 1;
       }
     
    //convert key character into integer   
    int key = atoi(argv[1]);
     
    //get string from user
    string text = GetString();
     
    //encipher text
     for(int i=0, n = strlen(text); i < n; i++)
        {
            if (islower(text[i]))
            {
                int new_text = ((((int)text[i]) + key - 97) %26) + 97; //change ASCII letter into integer
                printf("%c", new_text);
            }
             
            else if (isupper(text[i]))
            {
                int new_text = ((((int)text[i]) + key - 65) %26) + 65; //change ASCII letter into integer
                printf("%c", new_text);
            }
             
            else if (isdigit(text[i]) || isblank(text[i]))
            {
                printf("%c", text[i]);
            }
             
            else //repeated code, in case I have to change this last line later
            {
                printf("%c", text[i]);
            }
             
        }
     
    printf("\n");
     
    return 0;
}
     
/*
 
    extra code:
    {
    //print original letter, how many characters we are increasing it by with key, and then the new letter
    printf("\nOriginal: %c, Add: %d, New: %c", text[i], key, new_text);
    }
     
   int letter;
 
    printf("\nCalculating: %c + %d...\n", letter, key); 
     
    int result = (letter + key);
     
    printf("ASCII value of %c is %d \n\n", result, result);
     
    for (int i=0; i < argc; i++)
        for (int j=0, n = strlen(argv[i]); j < n; j++)
            printf("argv [%d][%d] is: %c\n", i, j, argv[i][j]);
   
 */          