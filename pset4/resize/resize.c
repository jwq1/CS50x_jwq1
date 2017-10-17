/**
 * Resizes the image to be factor of 'n' bigger than original.
 */

// Usage: ./resize n small.bmp large.bmp

// DONE: Implement a program called resize that resizes (i.e., enlarges) 24-bit uncompressed BMPs by a factor of n.

// DONE: Implement your program in a file called resize.c in a directory called resize.

// DONE: Your program should accept exactly three command-line arguments, whereby

// DONE: the first (n) must be a positive integer less than or equal to 100,

// DONE: the second must be the name of a BMP to be resized, and

// DONE: the third must be the name of the resized version to be written.

// DONE: + If your program is not executed with such, it should remind the user of correct usage, as with fprintf (to stderr), and main should return 1.

// Your program, if it uses malloc, must not leak any memory.

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n small.bmp large.bmp\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // print error if (n) is not a positive integer less than or equal to 100
    if (n > 100) {

        // print the n value given, and let user know how to fix their error.
        printf("You asked to increase the file size by a factor of %i.\n\n The factor, n, must be less than or equal to 100.\n Please try again.\n", n);

        // exit with error 1
        return 1;
    }


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
        return 1;
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
        return 1;
    }


    // Save the size of the original image, to scan over the pixels later

        // Width of Pixels
        int oldWidth = bi.biWidth;
        eprintf("oldWidth = %i\n", oldWidth);

        // Height of Pixels
        int oldHeight = abs(bi.biHeight);
        eprintf("oldHeight = %i\n", oldHeight);

        // Padding for image
        int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;;
        eprintf("oldPadding = %i\n\n", oldPadding);


    // Increase Width by n
        eprintf("Width before: %u\n", bi.biWidth);
        bi.biWidth = bi.biWidth * (n);
        eprintf("Width after: %u\n", bi.biWidth);

    // Increase Height by n
        eprintf("Height before: %u\n", abs(bi.biHeight));
        bi.biHeight = bi.biHeight * (n);
        eprintf("Height after: %u\n", abs(bi.biHeight));

    // determine padding for scanlines for new image
        int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        eprintf("newPadding = %i\n", newPadding);
        printf("\n");

    // Increase SizeImage by n
        // Should this be Height x Width?
        eprintf("SizeImage before: %u\n", bi.biSizeImage);
        // bi.biSizeImage = bi.biWidth * abs(bi.biHeight);
        // bi.biSizeImage = bi.biSizeImage * n;
        bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + newPadding) * abs(bi.biHeight);
        eprintf("SizeImage after: %u\n", bi.biSizeImage);

    // Add the new SizeImage to files bfSize
        // Should this be the size of the structure + the image size?
        eprintf("bfSize before: %u\n", bf.bfSize);
        // bf.bfSize = sizeof(BITMAPFILEHEADER) + bi.biSize + bi.biSizeImage;
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        eprintf("bfSize after: %u", bf.bfSize);
        printf(" = BITMAPFILEHEADER %lu + biSize %u + SizeImage %u\n", sizeof(BITMAPFILEHEADER), bi.biSize, bi.biSizeImage);
        printf("\n");


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0; i < oldHeight; i++)
    {

        // Set file position to beginning of the start of the i'th row.
        // This moves the file onto the next row.
            // The program becomes trapped in a single row otherwise.
        int rowPosition = (i * (oldWidth * sizeof(RGBTRIPLE) + oldPadding) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
        printf("\n\ninfile row %i = file position %i\n\n", i, rowPosition);
        fseek(inptr, rowPosition, SEEK_SET);

        // print the row n times
        for ( int m = 0; m < n; m++ ) {

            int inptrLoca = ftell(inptr);
            printf("writing infile row %i, to outfile %ix \n", i, m + 1);



            // iterate over pixels in scanline
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;


                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for(int l = 0; l < n; l++) {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            // skip over padding, if any
            fseek(inptr, oldPadding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }

        // Set file position at the beginning of the i'th row.
        // This affords the program the ability to repeatedly print out the row n times, giving it the proper height.
        fseek(inptr, inptrLoca , SEEK_SET);

        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
