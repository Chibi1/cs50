#include <stdio.h>
#include <cs50.h>


int main(void)
{

    int integer;
    // get integer from user
    do
    {
        printf("How high do you want your half pyramid?\n");
        integer = get_int("Integer: ");
    }
    while (integer < 0 || integer > 23);

    // draw pyramid
    for (int i = 0; i < integer; i++)
    {
        for (int j = 1; j < integer * 2 + 3; j++)
        {
            // prints empty space
            if (j < integer - i)
            {
                printf(" ");
            }
            else if (j >= integer - i && j < integer + 1)
            {
                // prints the first hash blocks
                printf("#");
            }
            else if (j >= integer + 1 && j < integer + 3)
            {
                // prints the middle space
                printf(" ");
            }
            else if (j >= integer + 3 && j < integer + i + 4)
            {
                // prints the second hash blocks
                printf("#");
            }
            // else
            // {
            //     // prints the the end empty spaces
            //     printf(" ");
            // }
        }
        // goes to next line of half pyramid
        printf("\n");
    }
}

