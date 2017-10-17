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
            printf("try again...program is quitting...\n");
            return 1;
       }
     
     
    //convert key characters into lowercase  
    for(int i=0; argv[1][i]; i++)
    {
        argv[1][i] = tolower((int)argv[1][i]);
         
        if (isalpha(argv[1][i]))
            continue;
        else
            printf("Only choose letters in the alphebet.\n");
            return 1;
    }
     
    //convert string into integer key
    int key = atoi(argv[1]);
     
    //get string from user
    string text = GetString();
     
    //encipher text
     for(int i=0, m = strlen(argv[1]), h = 0, n = strlen(text); i < n; i++)
        {
            if (islower(text[i]))
            {
                key = (argv[1][(i-h) %m]);
                int new_text = ((((((int)text[i]) + ((key - 97) %26)) - 97) %26) + 97); //change ASCII letter into integer
                printf("%c", new_text);
                 
            }
             
            else if (isupper(text[i]))
            {
                key = (argv[1][(i-h) %m]);
                int new_text = ((((((int)text[i]) + ((key - 97) %26)) - 65) %26) + 65); //change ASCII letter into integer
                printf("%c", new_text);
                 
            }
             
            else if (isdigit(text[i]) || isblank(text[i]))
            {
                h++;
                printf("%c", text[i]);
            }
             
            else //repeated code, in case I have to change this last line later
            {
                h++;
                printf("%c", text[i]);
            }
             
        }
     
    printf("\n");
     
    return 0;
}