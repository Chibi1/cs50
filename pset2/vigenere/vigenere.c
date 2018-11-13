#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    // check whether number of command line args = 1 (not including file name)
    if (argc <= 1 || argc >= 3)
    {
        printf("error[1]: Must input only one argument\n");
        return 1;
        void exit(int status);
    }
    else if (true)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (! isalpha(argv[1][i]))
            {
                printf("error[2]: Command line argument must be alphabetical with no spaces.\n");
                return 1;
                break;
                void exit(int status);
            }
        }

        // collecting key from user
        string key = argv[1];
        // get key length
        int keyLength = strlen(key);

        // collecting text to be encrypted
        string text = "";
        text = get_string("plaintext: ");
        // get string length
        int strLength = strlen(text);
        // printf("Length: %i\n", length);

        // obtain key ascii values for string shift
        char letter;
        int keyAsciiCode;
        int keyFormattedAscii;
        int keyNewAsciiCode;
        int keyShifts[100] = {};
        // char newLetter = 'a';
        // char cipher[length + 1];
        printf("ciphertext: ");
        for (int i = 0; i < keyLength; i++)
        {
            letter = key[i];
            // conversion to ascii
            keyAsciiCode = (int) letter;
            // upper or lower or special character (wrap implemented in nested if)
            if (isupper(letter))
            {
                keyFormattedAscii = keyAsciiCode - 65;
            }
            else if (islower(letter))
            {
                keyFormattedAscii = keyAsciiCode - 97;
            }
            else
            {
                keyFormattedAscii = keyAsciiCode;
            }
            // strcat(keyShifts, keyFormattedAscii);
            keyShifts[i] = keyFormattedAscii;
            // printf("%i", keyShifts[i]);
        }

        //perform cipher on input text
        int textAsciiCode;
        int textFormattedAscii;
        int textNewAsciiCode;
        int j = 0;
        for (int i = 0; i < strLength; i++)
        {
            letter = text[i];
            // conversion to ascii
            textAsciiCode = (int) letter;
            // assigning new ascii code after performing shift
            if (isalpha(letter))
            {
                textNewAsciiCode = textAsciiCode + keyShifts[j % keyLength];
                j++;
                //nested wrap implementation
                if (isupper(letter))
                {
                    if (textNewAsciiCode > 'Z')
                    {
                        textNewAsciiCode -= 26;
                    }
                }
                else if (islower(letter))
                {
                    if (textNewAsciiCode > 'z')
                    {
                        textNewAsciiCode -= 26;
                    }
                }

            }
            else
            {
                textNewAsciiCode = textAsciiCode;
            }

            printf("%c", textNewAsciiCode);
        }
        // printf("%i\n", keyShifts);
        printf("\n");
    }

}