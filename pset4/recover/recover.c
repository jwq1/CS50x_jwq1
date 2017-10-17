/*
Pseudo

1) Open memory card file

2) Find beginning of JPEG

3) Open new JPEG

4) Write 512 bytes until new JPEG is found

5) Detect end of file



*/


/*

Code snippets given in Walkthrough


Conditional to identify the beginning of a JPEG

    if (buffer[0] == 0xff &&
        buffer [1] == 0xd8 &&
        buffer [2] == 0xff &&
        (buffer [3] & 0xf0) == 0xe0 )


Name new files automatically

    sprintf(filename, "03i%.jpg", 2)

        filename: char array to store resultant string
            002.jpg

    FILE * img = fopen(filename, "w");




*/

// include required header files
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

// include some of our own typedefs
// #include"headerRecover.h"
typedef uint8_t BYTE;

int main (int argc, char * argv[]) {

    // Ensure we have taken in one command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover card.raw");
        return 1;
    }


    // Remember files
    char * infile = argv[1];


    // Ensure file can be opened
    FILE * inptr = fopen(infile, "r");

    if (inptr == NULL) {
        fprintf(stderr, "Could not open file");
        return 2;
    }

    // Create Files, variables, and storage needed below

        // Counter to track number of jpegs found
        int jpgctr = 0;


        // SAVE TO TEMPORARY STORAGE:
            // create temporary storage of 512 bytes as a buffer
        BYTE * buffer = malloc(512 * sizeof(BYTE));

        // Create an outfile image pointer
        FILE *img = NULL;

        // create filename starting from 000.jpg,
        // create filename variable (allocate memory);
            char *ftemplate = "000.jpg";
            int fLen = (strlen(ftemplate) + 1);
            char * filename = malloc(fLen);



    // REPEAT UNTIL EOF
    for (int i = 0, fiftyMB = pow(5,7); i <= fiftyMB ; i++ ) {


    // Check for 512 bytes in the memory card, infile.

        // If there is not 512 bytes, then stop, because you have reached EOF.

            // Set position to the correct starting point for loop.
            fseek(inptr, (512 * i), SEEK_SET);
            /*// Track where we are in memory
            if ((i%100) == 0)
                printf("stream[%i] = %li\n", i, ftell(inptr));*/


        if (fread(buffer, 1, 512, inptr) != 512) {
            printf("eof. close now.\n");
            return 0;
        }


    // else if there is 512 bytes then. Check for the beginning of a JPEG.


        // Set position to the correct starting point for loop.
            fseek(inptr, (512 * i), SEEK_SET);


        // SAVE TO TEMPORARY STORAGE:

            // overwrite what is in the buffer, the temporary storage of 512 bytes.
                fread(buffer, 1, 512, inptr);


        // if, yes beginning jpeg,

            if (buffer[0] == 0xff &&
                buffer [1] == 0xd8 &&
                buffer [2] == 0xff &&
                (buffer [3] & 0xf0) == 0xe0 ) {


            // Check to see if a jpeg file is already open.
            // check to see if the jpeg counter is greater than 0.
                    // If it is, then a previous file must have been created. Therefore, close that file.

                if (jpgctr > 0) {

                    // if yes, something is open, then close the previous file.
                    fclose(img);

                }

            // then start a new file
            // save the current 512 bytes to a new jpg file


                // CREATE FILENAME:

                        // write "03i%.jpg" to the filename character string, with the current jpeg number (e.g. 002.jpg for the second jpg found).
                            sprintf(filename, "%03i.jpg", jpgctr);


               // POINT to FILE:

                    // Open the file
                        img = fopen(filename, "w");



                // WRITE from BUFFER to the FILE:
                    fwrite(buffer, 1, 512, img);


                // KEEP COUNT OF JPG's FOUND:

                    // add 1 to the filename for every new jpeg
                        jpgctr++;



        // else, no begining of jpeg,


        } else if (jpgctr > 0) {


            // WRITE from BUFFER to the FILE:
                fwrite(buffer, 1, 512, img);


        }


    // Check next 512 bytes


    }



fclose(inptr);
fclose(img);
free(buffer);
return 0;
}

