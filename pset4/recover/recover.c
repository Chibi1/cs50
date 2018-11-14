// program which recovers deleted jpeg photos from a memory stick

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // check for correct number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "this program requires one argument\n");
        return 1;
    }

    // open memory card file
    FILE *pInFile = fopen(argv[1], "r");
    FILE *pOutFile = NULL;
    // check if file open was successful
    if (pInFile == NULL)
    {
        fclose (pInFile);
        fprintf(stderr, "could not open %s\n", argv[1]);
        return 2;
    }

    // obtain file size in bytes:
    fseek (pInFile , 0 , SEEK_END);
    int fileSize = ftell (pInFile);
    rewind (pInFile);

    const int memBlock = 512;
    // create memory allocation for inFile storage
    int *pBuffer = malloc(memBlock);
    int buffer;
    char *fileName[3];
    int counter = 0;
    int arr[fileSize];
    _Bool startJpeg;

    // for (int i = 0; i < fileSize; i += memBlock)
    while (!feof(pInFile))
    {
        fread(pBuffer, memBlock, 1, pInFile);
        buffer = *pBuffer;
        // check for jpeg signature match
        if (pBuffer[0] == 0xff &&
        pBuffer[1] == 0xd8 &&
        pBuffer[2] == 0xff &&
        (pBuffer[3] & 0xf0) == 0xe0)
        {
            startJpeg = true;
            sprintf(*fileName, "%3i.jpg", counter);
            FILE *img = fopen(*fileName, "w");
            fwrite(pBuffer, memBlock, 1, img); // if match, write block to pOutFile
            counter++;
        }
        // if not start of image
        else if (!(pBuffer[0] == 0xff &&
        pBuffer[1] == 0xd8 &&
        pBuffer[2] == 0xff &&
        (pBuffer[3] & 0xf0) == 0xe0))
        {
            startJpeg = false;
        }
        else if(startJpeg == false)
        {
            fwrite(pBuffer, memBlock, 1, pOutFile); // if match, write block to pOutFile
        }


    }


        //     fwrite(pBuffer, memBlock, 1, pOutFile);
        // }


    free(pBuffer);



}