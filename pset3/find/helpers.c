/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    
    // LINEAR SEARCH
    // // Your implementation must return false immediately if n is non-positive.
    // if(n < 0) {
    //     return false;
    // }
    
    // // Your implementation must return true if value is in values and false if value is not in values.
    // else {
        
    //     // look at the i'th value in the array, values[].
    //     for(int i = 0; i <= n; i++) {
            
    //         // if the value is within the array,
    //         if (value == values[i]) {
                
    //             // then return "true"
    //             return true;
                
    //         } 
            
    //     }
        
    // }
    
    
    
    
    // The running time of your implementation must be in O(log n).
        // Which means I have to implement binary search, rather than linear search.
    
    // BINARY SEARCH
        
    // Your implementation must return false immediately if n is non-positive.
        if(n < 0) {
            return false;
        }
    
    // Your implementation must return true if value is in values and false if value is not in values.
        
        int start, end;
            
            start = 0;
            end = n;
            
        
        do {
            
            int middle = (((end - start) / 2 ) + start);
            
            // eprintf("values[%i] = %i", middle, values[middle]);
            
            // if the value in the middle of the array is the searched for value,
            if(value == values[middle]) {
                
                // then return "true"
                return true;
            } 
            
            // else if, the searched for "value" is less than the value in the middle of the array, 
            else if (value < values[middle]) {
                
                // then, search left half of the list
                end = middle - 1;
                
                
                
            }
            
            // else if the searched for "value" is greater than the value in the middle of the array,
            else if (value > values[middle]) {
                
                // then search the right half of the array
                start = middle + 1;
                
                
            }
            
            
            
        }   while (start <= end);
    
    
    
    
    
    // You may not alter the function’s declaration. Its prototype must remain:
    return false;
}

/**
 * Sorts array of n values.
 */

// You may not alter the function’s declaration. Its prototype must remain:

void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    
    // Your implemenation must sort, from smallest to largest, the array of numbers that it’s passed.
    
    // The running time of your implementation must be in O(n2), where n is the array’s size.

    
    // BUBBLE SORT
    
    // Set swap counter to a non-zero value
        int swap = -1;
        // eprintf("swap = %i\n", swap);
    
    // Repeat until swap counter is zero
    while (swap != 0) {
        
        // Reset swap counter to zero
        swap = 0;
        // eprintf("swap = %i\n", swap);
        
        
        // while (swap <= n-2) {
            
        for (int i = 0, left = 0, right = 1; i < n ; i++) {   
            
        // Look at each adjacent pair
        // eprintf("values[%i] = %i\n", left, values[left]);
        // eprintf("values[%i] = %i\n", right, values[right]);
        
            
            // If two adjacent elements are not in order, swap them and add one to the swap counter
            if (values[left] > values[right]) {
                
                // store left-value in "swapper"
                int swapper = values[left];
                
                // change left-value to right-value
                values[left] = values [right];
                
                // set right-value to be "swapper", which is the original left-value.
                values[right] = swapper;
            
                // add one to the swap counter
                swap++;
                // eprintf("SWAP!\n\n");
                
                // look at next pair in the array
                left++;
                right++;
                
            } else {
                
                // look at next pair in the array
                left++;
                right++;
                
                
            }
           
        }
        
    }
    
    
    // Once the array is sorted, print the array.
    // for (int i = 0; i <= n ; i++) {   
            
    //     // Look at each adjacent pair
    //     eprintf("values[%i] = %i\n", i, values[i]);
        
    }
    
    
    
    return;
}
