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
        // Rubber Duck Talk 1:
            // Actual: for some reason I get 16 pixels across, while I only get 9 pixels down.
                // There is a single row of white pixels across the middle.
                    // This row seems to start 3 pixels over, then continues and wraps around to the next line.
                        // it ends 3 pixels from the right. 
                    // Essentially what seems to happen is the white pixels, which should be stacked on top of each other, 
                        // are saved 16 in a row, rather than 4x4. 
                    
                    // The question here is, for the middle rows, 
                        // how do I save 4 white pixels, 
                        // then 4 green pixels on the right
                        // then 4 more green pixels for the next line on the left
                        // then 4 more white pixels and so on.
                        // think about potentially using malloc? Seems like that is why they taught us about malloc.
                        
                        // Otherwise, I could try to think about printing one row at a time.
                            // Although I am not sure how I would do that. It would be like reading one full row of pixels
                            // then printing that row of pixels out 4x over.
                
                
                // The rest of the pixels are green
            // Expected: 12 pixels across (width) x 12 pixels down (height)
                // There should be a square of 4x4 white pixels in the middle
                // There should be large square of green pixel, which are 4 deep all the way around.
                
            
                
                
        
        // // write RGB triple to outfile
        //     // triple the width
        //     for (int k = 0; k < (n*n); k++) {
                
        //         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                    
        //     }
        
        
        
        
        // ==============================================================================================================================
        // // Rubber Duck Talk 2:
        //     // Actual: since I only printed 'n' times the pixels, it simply widened the image
                
        //     // Expected: 12 pixels across (width) x 12 pixels down (height)
        //         // There should be a square of 4x4 white pixels in the middle
        //         // There should be large square of green pixel, which are 4 deep all the way around.

        //     // write RGB triple to outfile
        //     // triple the width
        //     for (int k = 0; k < (n); k++) {
                
        //         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                    
        //     }
           
        
        
        
        // ==============================================================================================================================
        // // Rubber Duck Talk 3:
        //     // Actual: since I only printed 'n' times the pixels, it simply widened the image
                
        //     // Expected: 12 pixels across (width) x 12 pixels down (height)
        //         // There should be a square of 4x4 white pixels in the middle
        //         // There should be large square of green pixel, which are 4 deep all the way around.
 
            
        //     // write RGB triple to outfile
        //     // triple the width
        //     for (int k = 0; k < (n); k++) {
                
        //         // // triple the height
        //         // for (int l = 0; l < n; l++){
                
        //             fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                    
        //         // }
        //     }
        
        
        // ==============================================================================================================================
        // Rubber Duck Talk 4:
        
            // If the k for loop extends the Width by a factor of 'n'.
                // then I want to do that same action 'n' times
                // so that I get n rows printed out.
            
            
            // ATTEMPT 1:
            // I put a do the printing of the line n times around the original for loop.
                // I could do this with another for loop. Maybe I should. First let's see if it works.
            
            // do {
                
            //     int l = 0;
                
            //     for (int k = 0; k < (n); k++) {
                    
            //         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                        
            //     }
                
            //     l++;
            // }
            // while (l < n);   
            
             // ATTEMPT 2:
                // This resulted in the same layout as Rubber Duck Talk 1, when I used k < n*n.
                
                // This is looking at one pixel, then printing it four times. The pixels are stored in a row throughout memory.
                // However, we do not want to print one pixel at a time, we wnat to print one row at a time. 
                    // A row is 3 pixels in this case. However, we should make it work with any number of starting rows. 
                
                
            // for (int l = 0; l < n; l++) {
                
            //     for (int k = 0; k < (n); k++) {
                    
            //         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                        
            //     }

            // }
            
            // 0000036: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 000005a: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 000007e: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 00000a2: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 00000c6: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 00000ea: 00ff00 00ff00 00ff00 00ff00 ffffff ffffff ffffff ffffff ffffff ffffff ffffff ffffff  ....................................
            // 000010e: ffffff ffffff ffffff ffffff ffffff ffffff ffffff ffffff 00ff00 00ff00 00ff00 00ff00  ....................................
            // 0000132: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 0000156: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 000017a: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 000019e: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            // 00001c2: 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00 00ff00  ....................................
            
        
        
        
        // ==============================================================================================================================
        // Rubber Duck Talk 5:   
        // For this test, I increased the limit for the 
        
        // This prints 'n' times the number of original pixels
        for (int k = 0; k < n; k++) {
            
            
            char *pixelRow = malloc((sizeof((RGBTRIPLE) + 1) * sizeof(char));
                
                if (pixelRow == NULL)
                {
                    // Error w/ memory allocation
                    eprintf("\nError with malloc");
                    return 1;
                }
                
                free(pixelRow);
                    
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                        
        }
        
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

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
