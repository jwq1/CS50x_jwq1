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
        int reverseCtr = 0;
        
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
        
        // initalize memory to store a new row of pixels
        // RGBTRIPLE *row = malloc(bi.biWidth * sizeof(RGBTRIPLE));
        
        // set offset to restart the row
        
        // int sizeOfRGB = sizeof(RGBTRIPLE);
        // int offset = -abs(sizeOfRGB * (n));
        
            
          
                for (int k = 0; k < n; k++) {
                   
                    // This should save the row, into the memory of triple. 
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    
                    reverseCtr++;

            
                }                
                
                
        

        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }
    
        }   
        
        // Go back to beginning of line
        fseek(triple, -abs(reverseCtr), SEEK_CUR);       
        
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
