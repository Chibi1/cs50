#define _XOPEN_SOURCE

#include <unistd.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string hash;
int hashLen;
int saltLength;
char salt[2] = {};
string madeHash;

void alphaCheck ()
{
    // iteration of words and compare resulting hash
    char pass[6] = "";
    int passLength = 1;
    for (int i = 65; i < 124; i++)
    {
        // skip middle ascii characters
        if (i == 91)
        {
            i = 97;
        }
        // increase password checker by one letter
        else if (i == 123)
        {
            passLength++;
            i = 65;
            for (int j = 65; j < 124; j++)
            {
                // skip middle ascii characters
                if (j == 91)
                {
                    j = 97;
                }
                else if (i == 91)
                {
                    i = 97;
                }
                // increase password checker by one letter
                else if (i == 123)
                {
                    passLength++;
                    i = 65;
                    for (int k = 65; k < 124; k++)
                    {
                        // skip middle ascii characters
                        if (k == 91)
                        {
                            k = 97;
                        }
                        else if (j == 91)
                        {
                            j = 97;
                        }
                        else if (i == 91)
                        {
                            i = 97;
                        }
                        // increase password checker by one letter
                        else if (i == 123)
                        {
                            passLength++;
                            i = 65;
                            for (int l = 65; l < 124; l++)
                            {
                                // skip middle ascii characters
                                if (l == 91)
                                {
                                    l = 97;
                                }
                                else if (k == 91)
                                {
                                    k = 97;
                                }
                                else if (j == 91)
                                {
                                    j = 97;
                                }
                                else if (i == 91)
                                {
                                    i = 97;
                                }
                                // increase password checker by one letter
                                else if (i == 123)
                                {
                                    passLength++;
                                    i = 65;
                                    for (int m = 65; m < 124; m++)
                                    {
                                        // skip middle ascii characters
                                        if (m == 91)
                                        {
                                            m = 97;
                                        }
                                        else if (l == 91)
                                        {
                                            l = 97;
                                        }
                                        else if (k == 91)
                                        {
                                            k = 97;
                                        }
                                        else if (j == 91)
                                        {
                                            j = 97;
                                        }
                                        else if (i == 91)
                                        {
                                            i = 97;
                                        }
                                        // THE END
                                        else if (i == 123)
                                        {
                                            printf("No matching hash found.\n");
                                            return;
                                        }
                                        else if (j == 123)
                                        {
                                            j = 64;
                                            i++;
                                        }
                                        else if (k == 123)
                                        {
                                            k = 64;
                                            j++;
                                        }
                                        else if (l == 123)
                                        {
                                            l = 64;
                                            k++;
                                        }
                                        else if (m == 123)
                                        {
                                            m = 64;
                                            l++;
                                        }
                                        else
                                        {
                                            // asigning ascii values
                                            pass[passLength - 5] = i;
                                            pass[passLength - 4] = j;
                                            pass[passLength - 3] = k;
                                            pass[passLength - 2] = l;
                                            pass[passLength - 1] = m;
                                            // performing hash algorithm/check
                                            madeHash =  crypt(pass, salt);
                                            // printf("Password: %s --> Hash: %s\n", pass, madeHash);
                                            if (strcmp(madeHash, hash) == 0)
                                            {
                                                printf("%s\n", pass);
                                                return;

                                            }
                                        }
                                    }
                                }
                                else if (j == 123)
                                {
                                    j = 64;
                                    i++;
                                }
                                else if (k == 123)
                                {
                                    k = 64;
                                    j++;
                                }
                                else if (l == 123)
                                {
                                    l = 64;
                                    k++;
                                }
                                else
                                {
                                    // asigning ascii values
                                    pass[passLength - 4] = i;
                                    pass[passLength - 3] = j;
                                    pass[passLength - 2] = k;
                                    pass[passLength - 1] = l;
                                    // performing hash algorithm/check
                                    madeHash =  crypt(pass, salt);
                                    // printf("Password: %s --> Hash: %s\n", pass, madeHash);
                                    if (strcmp(madeHash, hash) == 0)
                                    {
                                        printf("%s\n", pass);
                                        return;

                                    }
                                }
                            }
                        }
                        else if (j == 123)
                        {
                            j = 64;
                            i++;
                        }
                        else if (k == 123)
                        {
                            k = 64;
                            j++;
                        }
                        else
                        {
                            // asigning ascii values
                            pass[passLength - 3] = i;
                            pass[passLength - 2] = j;
                            pass[passLength - 1] = k;
                            // performing hash algorithm/check
                            madeHash =  crypt(pass, salt);
                            // printf("Password: %s --> Hash: %s\n", pass, madeHash);
                            if (strcmp(madeHash, hash) == 0)
                            {
                                printf("%s\n", pass);
                                return;

                            }

                        }
                    }
                }
                else if (j == 123)
                {
                    j = 64;
                    i++;
                }
                else
                {
                    // asigning ascii values
                    pass[passLength - 2] = i;
                    pass[passLength - 1] = j;
                    // performing hash algorithm/check
                    madeHash =  crypt(pass, salt);
                    // printf("Password: %s --> Hash: %s\n", pass, madeHash);
                    if (strcmp(madeHash, hash) == 0)
                    {
                        printf("%s\n", pass);
                        return;

                    }
                }
            }
        }
        else
        {
            // asigning ascii value
            pass[passLength - 1] = i;
            // performing hash algorithm/check
            madeHash =  crypt(pass, salt);
            // printf("Password: %s --> Hash: %s\n", pass, madeHash);
            if (strcmp(madeHash, hash) == 0)
            {
                printf("%s\n", pass);
                return;

            }
        }
    }
}

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("error[1]: can only take one argument\n");
        return 1;
    }
    else {

        // store hashpassword
        hash = argv[1];
        hashLen = strlen(hash);
        // store "salt" (first two characters of hash)
        saltLength = 2;
        // printf("Salt: ");
        for (int i = 0; i < saltLength; i++)
        {
            salt[i] = hash[i];
            // printf("%c", salt[i]);
        }
        // printf("\n");

        alphaCheck();

        return 0;
    }
}

