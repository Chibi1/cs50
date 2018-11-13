// remove red noise from bmp files to reveal 'whodunit'

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"


int main(int argc, char * argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "error[1]: Must include two arguments\n");
        return 1;
    }

    // get filenames
    char * inputFileName = argv[1];
    char * outputFileName = argv[2];

    // open input file
    FILE * inputFileR = fopen(inputFileName, "r");
    if (inputFileR == 0) // check whether input file could be opened
    {
        fprintf(stderr, "error[2]: could not open input file\n");
        return 2;
    }

    // open output file
    FILE * outputFileR = fopen(outputFileName, "w");
    if (outputFileR == 0) // check whether output file could be opened
    {
        fclose(inputFileR);
        fprintf(stderr, "error[2]: could not open output file\n");
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputFileR);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputFileR);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputFileR);
        fclose(inputFileR);
        fprintf(stderr, "error[4]: Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputFileR);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputFileR);

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
            fread(&triple, sizeof(RGBTRIPLE), 1, inputFileR);

            // change red pixels to white pixels
            if (triple.rgbtRed == 255)
                {
                    triple.rgbtBlue = 255;
                    triple.rgbtGreen = 255;
                    triple.rgbtRed = 255;
                }
            if (triple.rgbtBlue != 255 || triple.rgbtGreen != 255 || triple.rgbtRed != 255)
                {
                    triple.rgbtBlue = 255;
                    triple.rgbtGreen = 0;
                    triple.rgbtRed = 0;
                }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFileR);
        }

        // skip over padding, if any
        fseek(inputFileR, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputFileR);
        }
    }

    printf("0");
    return 0;
}