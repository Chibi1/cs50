// program which recovers deleted jpeg photos from a memory stick

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // check for correct number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "this program requires one argument\n");
        return 1;
    }

    // remember infile name
    char *fOpen = argv[1];

    // open memory card file
    FILE *pInFile = fopen(fOpen, "r");
    FILE *pOutFile = NULL;
    // check if file open was successful
    if (pInFile == NULL)
    {
        fclose (pInFile);
        fprintf(stderr, "could not open %s\n", argv[1]);
        return 2;
    }

    BYTE pBuffer[512];
    const int memBlock = 512;
    char fileName[8];
    // fileName[7] = "\0";
    int counter = 0;

    while (fread(pBuffer, memBlock, 1, pInFile) == 1)
    {
        // check for jpeg signature match
        bool startJpeg = pBuffer[0] == 0xff && pBuffer[1] == 0xd8 && pBuffer[2] == 0xff && (pBuffer[3] & 0xf0) == 0xe0;

        // check whether signature match and whether a match has already been found
        if (startJpeg && pOutFile != NULL)
        {
            fclose(pOutFile);
            counter++;
        }

        // check signature so file is opened
        if(startJpeg)
        {
            sprintf(fileName, "%03i.jpg", counter);
            pOutFile = fopen(fileName, "w");
        }

        // whenever cursor is inside jpeg image
        if(pOutFile != NULL)
        {

            fwrite(pBuffer, memBlock, 1, pOutFile); // if match, write block to pOutFile
        }
    }

    // close last output file
    fclose(pOutFile);

    // close input file
    fclose(pInFile);

    return 0;
}