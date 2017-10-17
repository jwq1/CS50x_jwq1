/*Rubber duck talk


1) TODO: Hexidecimals per byte
    A hexidecimal is stored in 4 bits. That means each byte contains two hexidecimal digits.
        What does that mean for how I access the hexidecimals?

    Is there only one hexidecimal in each byte, leaving extra space for ______?
            If yes, then I would look at each byte of the block of memory, 512 of them, to copy that memory over to a new block of memory.


2) DONE: BYTES of memory in a block
    How many bytes are in a block of a memory card?
        512

    Then I should one block over at a time. Each time I would check to see if it was the start of a new JPEG,
    or the end of the file. until I got to the end of the jpg files.

    Start of new JPG, means save to a new file.

    End of the file, means no more JPGs to be found and I can close everything.

    Note: The end is indicated by a block of memory that does not contain 512 bytes.

3) TODO: Pointers and Dynamic Memory:

   Dynamic memory, malloc, only give back a pointer to a chunk of memory of specified size.

   Once the pointer is given back, data has to be stored into the allocated memory.

   This has to happen before I can look up values stored at a particular memory location.
        (e.g. &block[_] requires me to have stored a value in the memory at block.)

    To store values at the memory pointed to by _______ pointer, do I need to dereference the pointer?

4) TODO: Where in the stream to begin reading memory card

    I think I have to skip the first 512 bytes, first block, of memory.


*/

/**
 * Recovers JPEGs from a memory card
 */

// Header

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "headerRecover.h"



// Begin main, accept 1 argument
int main(int argc, char *argv[])
{
    // ensure there is only one command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    // remember file name
    char *infile = argv[1];


    // Open card file
    FILE * inptr = fopen(infile, "r");

        // if file does not open, then print error.
        if (inptr == NULL)
        {
            // print error "Could not open filename"
            fprintf(stderr, "Could not open %s.\n", infile);
            return 2;
        }


    // intialize jpeg counter
    int jpgCtr = 0;

    // set stream past the first block
    fseek(inptr, 512 * sizeof(BYTE), SEEK_SET);

    // check whether stream is at 512
    int stream = ftell(inptr);
    printf("stream placement = %i\n", stream);



    // buffer
    // temporary storage
    // initialize a pointer to a chunk of memory that matches the size of a block
    BYTE * blockptr = malloc(512 * sizeof(BYTE));

    // store a variable in that chunk of memory
    BYTE block =

    int block[512];

    // repeat until end of card
    while(fread(&block, 1, sizeof(MEMBLOCK), inptr) == sizeof(MEMBLOCK))
        {

        // count how many times I loop
        jpgCtr++;
        // eprintf("loop %i\n", jpgCtr);

        // read 512 bytes into buffer
        fread(&block, 1, 512, inptr);

        // error
        eprintf("block[%i]\n", block[jpgCtr]);


        // start of a new JPEG?
        if (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            (block[3] & 0xf0) == 0xe0) {

            printf("start of new jpg %li\n", ftell(inptr));

            }


        }


    fclose(inptr);



//             // yes ->

//                 // close the previous file
//                 fclose(filename);

//                 // keep track of how many JPEGs we have opened thus far
//                 jpgCtr++;

//                 // print new .jpg file
//                 sprintf(filename, "%03i.jpg", jpgCtr);

//                 // open our new file
//                 FILE *img = fopen(filename, "w");


//                 fwrite(&block, sizeof(MEMBLOCK), 1, img);


//             // no ->

//                 // check to see if we already found a JPEG

//             }

//         // already found a JPEG?
//             else if (jpgCtr > 0) {

//                 // yes ->

//                     // then the 512 bytes belong to the current JPEG file
//                     // write 512 bytes into current JPEG file
//                     fwrite(&block, sizeof(MEMBLOCK), 1, img);


//                     // increase JP





//                 // no ->

//                     // discard those 512 bytes and go back to loop


//                 // yes ->

//                     // then the 512 bytes belong to the current JPEG file

//                     // write 512 bytes into current JPEG file

//                     // increase JP



//         }


//     }















//     // read file



//         // read file, store values into buffer
//             // read from the file stored a memptr, in one element of size MEMBLOCK,
//             // save to block, the buffer.
//         fread(&block, sizeof(MEMBLOCK), 1, memptr);


//     // Find the start of a JPEG

//         if (buffer[0] == 0xff &&
//             buffer[1] == 0xd8 &&
//             buffer[2] == 0xff &&
//             (buffer[3] & 0xf0) == 0xe0) {



//                 FILE *img = fopen(filename, "w");

//                 fwrite(block, sizeof(MEMBLOCK), 1, img)



//             }

//         // print new .jpg file
//         sprintf(filename, "%03i.jpg", 2);
//                     // filename: char array to store the resultant stirng
//                         // 002.jpg

//     // Keep track of the jpg's I have found thus far
//     int jpgCtr = 0;










// // extra code;
//     // Create file to store new jpg in
//     // TODO: Get size of n
//     BYTE *jpgFile = malloc(n * sizeof(MEMBLOCK));


//     // Open jpgFile in write mode
//     FILE *jpgptr = fopen(jpgFile, "w");
//

}