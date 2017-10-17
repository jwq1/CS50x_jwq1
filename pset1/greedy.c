#include <stdio.h>
#include <cs50.h>
#include <math.h>
 
int main (void)
 
{
 
float change;
int cents;
int quarter = 0;
int dime = 0;
int nickel = 0;
int penny = 0;
int coins = 0;
 
 
 
    do
    {
        printf("How much change is owed?\n$");
        change = GetFloat();
    }
    while (change < 0);
     
    cents = round(change * 100);
 
 
    while (cents > 0)
    {
          if (cents >= 25)
          {
            ++quarter;
            cents = (cents - 25);
          }
          else if (cents >= 10)
          {
            ++dime;
            cents = (cents - 10);
          }
          else if (cents >= 5)
          {
            ++nickel;
            cents = (cents - 5);
          }
          else
          {
            ++penny;
            cents = (cents - 1);
          }
    }
     
    /*
    printf ("You will recieve %d quarters back. \n", quarter);
    printf ("You will recieve %d dimes back. \n", dime);
    printf ("You will recieve %d nickels back. \n", nickel);
    printf ("You will recieve %d pennies back. \n", penny);    
    printf ("You will recieve %d coins back. \n", coins);
    */
     
    coins = quarter + dime + nickel + penny;
     
    printf ("%d\n",coins);
}