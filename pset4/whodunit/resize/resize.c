// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    // integer bounds
    if (atoi(argv[1]) < 0 || atoi(argv[1]) > 100)
    {
        fprintf(stderr, "error[2]: argument one must be between 1 and 100");
    }

    // file types for input and output files
    const char* a[2];
    a[0] = &argv[2][strlen(argv[2]) - 3];
    a[1] = &argv[3][strlen(argv[3]) - 3];
    if (strcmp(a[0], "bmp") != 0 || strcmp(a[1], "bmp") != 0)
    {
        fprintf(stderr, "error[3]: file types must be bmp\n");
        return 1;
    }

    // store scale
    int scaling = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
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

    // new dimensions
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    int newWidth = oldWidth * scaling;
    int newHeight = oldHeight * scaling;

    int oldPadding;
    int newPadding;

    // calculate scaling
    bi.biWidth = newWidth;
    bi.biHeight = newHeight;
    oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4; // determine padding for scanlines
    newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4; // determine padding for scanlines
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + newPadding) * abs(newHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);



    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // allocate a memory to store one scanline
    RGBTRIPLE scanLine[newWidth * sizeof(RGBTRIPLE)];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
       // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // create a new scanline in a temporary array
            for (int k = 0; k < scaling; k++)
            {
                scanLine[(j * scaling) + k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        // write the current scanline n times
        for (int j = 0; j < scaling; j++)
        {
            // write a new scanline once
            fwrite(scanLine, sizeof(RGBTRIPLE), newWidth, outptr);

            // write new padding
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
