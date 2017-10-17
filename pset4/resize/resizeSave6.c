/**
 * Resizes the image to be factor of 'n' bigger than original.
 */

// Usage: ./resize n small.bmp large.bmp

// Implement a program called resize that resizes (i.e., enlarges) 24-bit uncompressed BMPs by a factor of n.

// DONE: Implement your program in a file called resize.c in a directory called resize.

// Your program should accept exactly three command-line arguments, whereby

// the first (n) must be a positive integer less than or equal to 100,

// the second must be the name of a BMP to be resized, and

// the third must be the name of the resized version to be written.

// + If your program is not executed with such, it should remind the user of correct usage, as with fprintf (to stderr), and main should return 1.

// Your program, if it uses malloc, must not leak any memory.



#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Your program should accept exactly three command-line arguments, whereby
    // argc needs to equal 4, because argc 1 is the command to run the program,
        // rather than an argument
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }



    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // Save the size of the original image, to scan over the pixels later

        // Width of Pixels
        int oldWidth = bi.biWidth;
        eprintf("oldWidth = %i\n", oldWidth);

        // Height of Pixels
        int oldHeight = abs(bi.biHeight);
        eprintf("oldHeight = %i\n", oldHeight);

        // Padding for image
        int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;;
        eprintf("oldPadding = %i\n\n", oldPadding);


    // Increase Width by n
        // A) account for padding (remove padding, then add it back in)
        // B) remember to save the original height
            // to scan over the pixels in the original image later.

        eprintf("Width before: %u\n", bi.biWidth);
        bi.biWidth = bi.biWidth * (n);
        eprintf("Width after: %u\n", bi.biWidth);

    // Increase Height by n
        eprintf("Height before: %u\n", abs(bi.biHeight));
        bi.biHeight = bi.biHeight * (n);
        eprintf("Height after: %u\n", abs(bi.biHeight));

    // Increase SizeImage by n
        // Should this be Height x Width?
        eprintf("SizeImage before: %u\n", bi.biSizeImage);
        // bi.biSizeImage = bi.biWidth * abs(bi.biHeight);
        bi.biSizeImage = bi.biSizeImage * n;
        eprintf("SizeImage after: %u\n", bi.biSizeImage);

    // Add the new SizeImage to files bfSize
        // Should this be the size of the structure + the image size?
        eprintf("bfSize before: %u\n", bf.bfSize);
        bf.bfSize = sizeof(BITMAPFILEHEADER) + bi.biSize + bi.biSizeImage;
        eprintf("bfSize after: %u", bf.bfSize);
        printf(" = BITMAPFILEHEADER %lu + biSize %u + SizeImage %u\n", sizeof(BITMAPFILEHEADER), bi.biSize, bi.biSizeImage);
        printf("\n");

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines for new image
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    eprintf("newPadding = %i\n", newPadding);
    printf("\n");


    // iterate over infile's scanlines
    for (int i = 0; i < oldHeight*n; i++)
    {


        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);


        // run this command to see the large image pixels in the command-line hex editor
            // xxd -c 36 -g 3 -s 54 large.bmp

        // run this command to see the small image pixels
            // xxd -c 12 -g 3 -s 54 small.bmp
                // It uses -c 12, because there are actually 4 columns w/ 4 bytes. 3 rgbtriples and 1 padding.
                // Therefore to see the large image pixels, which is 3 pixels x 4 = 12 pixels (a multiple of 4)
                    // to correctly see the 12 pixels, we do not need to include padding, we can just print 36 bytes per row.
                    // hence -c is 36, not 48, as one might expect from multiple -c 12 by a factor of n = 4.


        // ==============================================================================================================================
        // Rubber Duck Talk 6:

        //  Basically we want to do one of two things. We can either write a structure which consists of one row of RGBTRIPLES
            // or create a file, which would store n elements, of size RGBTRIPLE, and save that bi.biWidth times over
                // This would store a row, then we could leave that for loop, enter another for loop
                    // which prints out the new line of the image n times over.

        // first we want to read from the infile
        // store in buffer
        // write from buffer to middlefile
            // write n times (n pixels)
        // read from middle file
            // store middlefile in a new buffer2
            // store the row as one element in the buffer
        // write from the buffer2 to the outptr
            // write n times (n rows)



        // Revision to above plan
        // What if we don't save the row to a file, but rather to a variable?
        // A variable which is a custome structure, defined in a header file?

        // Could we create a "create/store/save row" function to save the row information in a variable,
            // then recursively call the variable to print the rows out?


            // Then we would
                // 1. Dynamically size an array (dynamic memory) to hold a row of pixels
                // 2. Create a function to store the row of pixels
                // 3. Define a variable for the function to return (typedef/structure)
                // 4. Recursively call that function (recursion/call stack)
                // 5. Use a file pointer to store those rows in the correct file (file pointers)




        // STEP 1: Create a buffer that can hold a row of information

            // This row will be RGBTRIPLE * n * oldWidth
                // ^^^ can this buffer be created? How?
                // Let's create a variable that stores the number of pixels in a row
                    // int rowPixels = n * oldWidth * sizeof(RGBTRIPLE);

                // Then set an array of RGBTRIPLEs which can hold a row's worth of RGBTRIPLE pixels.
                    // RGBTRIPLE row[rowPixels];
                    // ^^^ unfortunately we cannot set a dynamic variable into the array, we need malloc

                // allocate memory to hold a row's worth of pixels, rowPixels.
                // Set each element must be the size of a pixel, RGBTRIPLE

                // Create a pointer to memory which contains information of type RGBTRIPLE
                // Make sure the size of the array is a row's worth of pixels, each of size RGBTRIPLE
                    // RGBTRIPLE *row = malloc(rowPixels);


                // STEP 1 Summary:
                // This should then be an array that can store a rows worth of, rowPixels, of RGBTRIPLE elements.
                // We can then use this buffer, &row, to store 1 element, which is the size of a row, containing one row of new pixels.



        // STEP 2: write to a file which will store the row

            // STEP 2.1: create file to write to
            // FILE *rowStorage = fopen(outfile, "w");


            // STEP 2.12: open file in write mode


            // STEP 2.2: read from the buffer element and store it in a file, until you get to the end of the row.
                // note: end of the row is indicated by the oldWidth of the element
                // note: you'll have to skip over the padding before you start at the next row


            // STEP 2.3: do this n times over (use the same buffer element, do not progress)




        // STEP 3: write that row to the output file n times

            // STEP 3.12: open file which contains the row in read mode

            // STEP 3.13: create buffer, &row

            // STEP 3.14: save a variable that is the size of the row,
                // this will indicate the size of the element

            // STEP 3.14: read from file and store it in the &row buffer as one element


            // STEP 3.2: write from &row buffer, to the output file in one element.
                // obsolete note: single row should include, oldWidth # of elements, of size RGBTRIPLE * n.
                    // (&[insert buffer file] , sizeof(RGBTRIPLE) * n, oldWidth, outptr)



            // STEP 3.3: if any new padding is required for the new row, add it here, before you progress to next row.


            // STEP 3.4: loop through this n times to print the required number of rows.



                // for (int k = 0; k < n; k++) {

                //     // This should save the row, into the memory of triple.
                //     fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                //     reverseCtr++;


                // }




        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }

        }



    }

    // // free memory
    // free(pixelRow);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
