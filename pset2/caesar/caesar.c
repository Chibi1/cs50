#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    // check whether number of command line args = 1 (not including file name)
    if (argc <= 1 || argc >= 3)
    {
        printf("error[1]: Must input one argument\n");
        return 1;
    }

    // whether called command line arg is positive integer
    if (atoi(argv[1]) > 0)
    {
        // collecting key from user
        int key = atoi(argv[1]);
        int formattedKey = key % 26;

        // collecting text to be encrypted
        string text = "";
        text = get_string("plaintext: ");
        // get string length
        int length = strlen(text);
        // printf("Length: %i\n", length);

        // cycle through each character of text and apply key
        char letter;
        int asciiCode;
        int formattedAscii;
        int newAsciiCode;
        char newLetter = 'a';
        char cipher[length + 1];
        printf("ciphertext: ");
        for (int i = 0; i < length; i++)
        {
            letter = text[i];
            asciiCode = (int) letter;
            // upper or lower or special character (wrap implemented in nested if)
            if (asciiCode >= 'A' && asciiCode <= 'Z')
            {
                newAsciiCode = asciiCode + formattedKey;
                if (newAsciiCode > 'Z')
                {
                    newAsciiCode -= 26;
                }
            }
            else if (asciiCode >= 'a' && asciiCode <= 'z')
            {
                newAsciiCode = asciiCode + formattedKey;
                if (newAsciiCode > 'z')
                {
                    newAsciiCode -= 26;
                }
            }
            else
            {
                newAsciiCode = asciiCode;
            }
            printf("%c", newAsciiCode);
            // cipher[i] = ;
        }
        printf("\n");



        // printf("key: %i\n", key);
        // printf("ciphertext: %s\n", cipher);
    }
    else
    {
        printf("error[2]: Command line argument must be positive integer\n");
    }


}