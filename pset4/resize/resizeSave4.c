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

    // // Initialize pointer pixelRow, which will store RGBTRIPLEs in it.
    // RGBTRIPLE* pixelRow = malloc((bi.biWidth * sizeof(RGBTRIPLE)));
    
    // if (pixelRow == NULL)
    //             {
    //                 // Error w/ memory allocation
    //                 eprintf("\nError with malloc");
    //                 return 1;
    //             } 
    

    // iterate over infile's scanlines
    for (int i = 0; i < oldHeight; i++)
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
        // Rubber Duck Talk 5:   
        // For this test, I increased the limit for the 
        
        // The earlier fread line, reads from one spot (pixel) in the array at address &triple.
            // The the next function, uses a for loop, to print that pixel out four times.
            // This information is saved in the memory block at outptr.
            // However, this memory block is 'n' times the height
                // Therefore, once a row is saved to outptr, that same row, should be saved 4 more times.
        
       
       
       //RELATED TO MALLOC: The size of this memory block should be the Width of the new image file. 
                // malloc accepts this width in bytes. Let malloc know how many bytes we need to store the width.
                // The width of the new image file is bi.biWidth, which is what I set it to earlier.
                    // Do I need to convert bi.biWidth into the number of bytes it is? How? Since bi.biWidth is a DWORD.
                // Once I figure out the bytes in bi.biWidth, then how do I pass that into malloc?
                    // What does size_t mean? What information do I put there?
                
            // NOTE:
                // Syntax
                //     sizeof( type )	(1)	
                //     sizeof expression	(2)	
                //     Both versions return a constant of type std::size_t.
        
        //RELATED TO MALLOC: Also, why does pixleRow need to be in a FILE format? 
            // Does that format make sense to pull from when I write to outptr?
            // What does a FILE format look like, or even mean? I thought everything got saved as blocks of memory.
        
        
        // store memory the size of the width of the image (in pixels), multiplied by the size of the RGBTRIPLE struct, which is 3 bytes.
                // In this case we have allocated bi.biWidth, which is 12 pixels wide, by 3 bytes, which equals 36 bytes of memory.
                // That is the size of a row in our new image.
        
        // // Initialize pointer pixelRow, which will store RGBTRIPLEs in it.
        // FILE* pixelRow = malloc((bi.biWidth * sizeof(RGBTRIPLE)));
        
        // To write this row 'n' times in my outfile, then I should recursively write this function 'n' times over.
            // Review the recursion video, along with typedef and structure videos to see if we can create another function.
            // the function could be called recursively to print the desired number of rows, using n! as the limit for the recursion.
                
                // if (pixelRow == NULL)
                // {
                //     // Error w/ memory allocation
                //     eprintf("\nError with malloc");
                //     return 1;
                // } 
                
                
        // Now store the color of pixel at &triple[j] in &pixelRow[k]. 
            // I am not sure if that is what this function is doing............
            
        for (int k = 0; k < n; k++) {
            
            
                    // This should save the row, into the memory of pixelRow. 
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);         
                    
                    
                    // Does fwrite only write to files? Probably. 
                    // error:incompatible pointer types passing 'RGBTRIPLE *' to parameter of type 'FILE *' 
                
                    // 
                
                    
        }       
                
                    
        // // I should then be able to take the information at &pixelRow, and store it 'n' times into the outptr memory.
        // for (int l = 0; l < n; l++) {
            
        //     fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
        
        // }                   
        
        
        // When one row is printed, we want to print that row out, another 'n' times.
            // What if we stored the output from the above write function, 
                // which outputs one row, 
                // into memory, not associated w/ outptr. 
            // Then we write that row into outptr 'n' times.
        
        
        
        
            
        }
       

        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
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
