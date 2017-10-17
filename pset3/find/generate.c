/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // TODO: comment me
    // If generate receives anything other than 2 or 3 arguments,
    if (argc != 2 && argc != 3)
    {
        // then print instructional error message
        printf("Usage: ./generate n [s]\n");
        // exit program with return value of 1
        return 1;
    }

    // TODO: comment me
    // initialize variable n as an integer.
    // set variable n to the integer value of argv[1], the second argument.
    int n = atoi(argv[1]);

    // TODO: comment me
    // If three arguments were provided
    if (argc == 3)
    {
        // then seed the pseudo random number generator with the value of the third argument.
        srand48((long) atoi(argv[2]));
    }
    else
    {
        // else, see the pseudo random number generator with the present time on the computer.
        srand48((long) time(NULL));
    }

    // TODO: comment me
    // While i is less than n, the second argument,
    for (int i = 0; i < n; i++)
    {
        // then print each successive integer produced by the pseudo random number generator.
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
