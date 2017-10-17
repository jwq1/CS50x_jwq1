// SPEC 1: TODO
// Implement a program called resize that resizes (i.e., enlarges) 24-bit uncompressed BMPs by a factor of n.

// ./resize 4 small.bmp large.bmp


#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


// SPEC 2: COMPLETE
// Implement your program in a file called resize.c in a directory called resize.

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        
        // SPEC 3: COMPLETE
        // Your program should accept exactly three command-line arguments, whereby
        fprintf(stderr, "Usage: ./resize n small.bmp large.bmp\n");
        return 1;

        
    }
    

    // remember filenames
    char *n = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];

    
    // SPEC 4: COMPLETE
    // the first (n) must be a positive integer less than or equal to 100,

    if (*n <= 0 || *n > 100) {
        
        fprintf(stderr, "(n) must be a positive integer less than or equal to 100\n");
        return 1;
        
    }

    // SPEC 5: COMPLETE
    // the second must be the name of a BMP to be resized, and

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // SPEC 6: COMPLETE
    // the third must be the name of the resized version to be written.

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

    
    // Increase relevant fields in structural files
    printf("BEFORE bf.bfSize = %u\n", bf.bfSize );
    
    int factor = *n;
    
    bi.biWidth = bi.biWidth * factor;
    
    bi.biHeight = bi.biHeight * factor;
    
    bi.biSizeImage = bi.biSizeImage * factor;
    
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
    
    printf("AFTER bf.bfSize = %u\n", bf.bfSize );
    
    
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    
    
    

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            
            // write RGB triple to outfile
            // for (int k = 0; k < factor; k++) {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            // }
            
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}


// SPEC 7: COMPLETE (see spec 4, 5, 6 above)
// + If your program is not executed with such, it should remind the user of correct usage, as with fprintf (to stderr), and main should return 1.


// SPEC 8: TODO
// Your program, if it uses malloc, must not leak any memory.