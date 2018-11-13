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
        for (int j = 0; j < integer + 1; j++)
        {
            // prints empty space
            if (j < integer - 1 - i)
            {
                printf(" ");
            }
            else
            {
                // prints the hash blocks
                printf("#");
            }
        }
        // goes to next line of half pyramid
        printf("\n");
    }
}

