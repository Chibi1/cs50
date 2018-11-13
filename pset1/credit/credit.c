#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
    // get card number
    long long number;
    number = get_long_long("Number: ");
    long long number_copy = number;

    // convert number into string
    char numberStr[20];
    sprintf(numberStr, "%lld", number);

    //get number length
    int length;
    length = strlen(numberStr);
    // printf("Number Length: %i\n", length);

    //grab first two digits of number
    char firstTwoDigits[2];
    for(int i = 0; i < 2; i++)
    {
        // printf("%c\n", numberStr[i]);
        firstTwoDigits[i] = numberStr[i];
        // strcpy(&firstTwoDigits[i], &numberStr[i]);
    }


    // obtain every second digit starting from the last digit
    char stepTwo[10] = "";
    int stepTwoLen;
    for(int i = length - 1; i >= 0 && i < length; i -= 2)
    {
        stepTwoLen = strlen(stepTwo);
        stepTwo[stepTwoLen] = numberStr[i];
    }
    // memmove(stepTwo, stepTwo+1, strlen(stepTwo));
    printf("Last: %s\n", stepTwo);



    // obtain every second digit starting from the second last digit
    char stepOne[20];
    int stepOneLen;
    for(int i = length - 2; i >= 0; i -= 2)
    {
        stepOneLen = strlen(stepOne);
        stepOne[stepOneLen] = numberStr[i];
    }
    printf("Second Last: %s\n", stepOne);


    // Calculation step 1: multiply stepOne digits
    // char calc[stepOneLen];
    // int stepThree[20];
    // // sscanf(stepOne, "%d", &k);
    // for(int i = 0, n = stepOneLen; i < n; i++)
    // {
    //     stepThree[i] = atoi(&stepOne[i]);
    //     calc[i] = 2 * stepThree[i];
    // }



    // Calculation step 1: multiply stepOne digits (Second Try)
    // int digit;
    // unsigned int calc[20];
    // while(number_copy) {
    //     digit = number_copy % 10;
    //     number_copy /= 10;

    //     // Do something with digit
    //     for(int i = 0; i < stepOneLen; i++)
    //     {
    //         calc[i] = 2 * fmod(number_copy, pow(i, 10));
    //     }


    // }




    // printf("%c\n", calc);

    printf("Number Length: %i\n", length);
    printf("Number stringified: %s\n", numberStr);
    printf("First two digits: %s\n", firstTwoDigits);
}
