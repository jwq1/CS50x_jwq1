#include <stdio.h>
#include <cs50.h>
#include <math.h>
 
int main (void)
 
{
 
int spaces;
int width;
int height;
int row_num;
    
   do
   {
        printf("Height: ");
        height = GetInt();
        (row_num = height);
        if (height == 0)
        {
            return 0;
        }
   }
   while ( height < 0 || height > 23 );

   do
   { 
        for (spaces = 1; spaces <= (row_num - 1); spaces++)
        {
            printf(" ");
        } 
     
        for (width = 0; width <= ((height + 1) - spaces); width++) 
        {
            printf("#");
        } 
         
        printf("\n");
         
        if (row_num > 0)
        {
            (row_num = row_num - 1);
        }
         
   }
   while (row_num > 0);
}