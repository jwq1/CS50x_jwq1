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

    // Error check
    int loopCtr = 0;

    // buffer
    int *block = malloc(512 * sizeof(BYTE));

    // create pointer to the jpg file
    FILE * jpgptr;

    // repeat until end of card
    while(fread(&block, 1, sizeof(MEMBLOCK), inptr) == sizeof(MEMBLOCK))
        {

        // count how many times I loop
        loopCtr++;
        eprintf("loop %i\n", loopCtr);

        // read 512 bytes into buffer
        fread(&block, 1, 512, inptr);

        // create string for name of the jpg file
        char *filename = "000.jpg";

        // start of a new JPEG?
        if (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            (block[3] & 0xf0) == 0xe0) {

                if (jpgCtr == 0) {

                    // print new .jpg file
                    sprintf(filename, "%03i.jpg", jpgCtr);

                    jpgptr = fopen(filename, "w");

                    jpgCtr++;

                } else {

                    fclose(jpgptr);

                    // print new .jpg file
                    sprintf(filename, "%03i.jpg", jpgCtr);

                    jpgptr = fopen(filename, "w");

                    jpgCtr++;
                }



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