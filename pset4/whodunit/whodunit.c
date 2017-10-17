// SPEC 1: COMPLETE
// Implement your program in a file called whodunit.c in a directory called whodunit.


// SPEC 2: COMPLETE
// Your program should accept exactly two command-line arguments: the name of an input file to open for reading followed by the name of an output file to open for writing.

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {

        // SPEC 3: COMPLETE
        // If your program is executed with fewer or more than two command-line arguments, it should remind the user of correct usage, as with fprintf (to stderr), and main should return 1.
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;

    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];





// SPEC 4: COMPLETE
// If the input file cannot be opened for reading, your program should inform the user as much, as with fprintf (to stderr), and main should return 2.

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

// SPEC 5: COMPLETE
// If the output file cannot be opened for writing, your program should inform the user as much, as with fprintf (to stderr), and main should return 3.

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }






// SPEC 6: COMPLETE
// If the input file is not a 24-bit uncompressed BMP 4.0, your program should inform the user as much, as with fprintf (to stderr), and main should return 4.

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

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

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
            
            
            // If the square is completely red, then turn it white.
            if (triple.rgbtRed == 0xff && triple.rgbtGreen == 0x00 && triple.rgbtBlue == 0x00) {
                
                triple.rgbtGreen = 0xff;
                triple.rgbtBlue = 0xff;
                
            // Else, if the square is not completely white, then turn it black. 
            // (not working as intended.)
            } else if (triple.rgbtRed != 0xff && triple.rgbtGreen != 0xff && triple.rgbtBlue != 0xff ) {
                
                triple.rgbtGreen = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0x00;
                
            }
            
            
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
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


// SPEC 7: COMPLETE
// Upon success, main should 0.

    // success
    return 0;    
    


// End of 'main' function
}