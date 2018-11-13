// This program calculates how much change is required to be given

#include <stdio.h>
#include <cs50.h>
#include <math.h>

 enum Coins {
    QUARTER,
    DIME,
    NICKEL,
    PENNY
} coin;

int main(void)
{
    double change;
    int changeInt;
    do
    {
        // Initial question
        // printf("How much change is owed?\n");
        change = get_double("Change owed: ");
        changeInt = change * 100;
    }
    while (changeInt < 0);

    // Establishing change amounts
    double quaters_25 = 0.25;
    double dimes_10 = 0.10;
    double nickels_5 = 0.05;
    double pennies_1 = 0.01;

    int quatersInt = quaters_25 * 100;
    int dimesInt = dimes_10 * 100;
    int nickelsInt = nickels_5 * 100;
    int penniesInt = pennies_1 * 100;

    // Count count varialbles
    int quater = 0;
    int dime = 0;
    int nickel = 0;
    int penny = 0;

    printf("Calculating...\n");
    // begin counting change
    int sum = 0.00;

    while(sum < changeInt)
    {
        int x = changeInt - sum;

        if (x >= quatersInt)
        {
            coin = QUARTER;
        }
        else if (x >= dimesInt)
        {
            coin = DIME;
        }
        else if (x >= nickelsInt)
        {
            coin = NICKEL;
        }
        else if (x >= penniesInt)
        {
            coin = PENNY;
        }

        switch(coin)
        {
            case (QUARTER):
                sum = sum + quatersInt;
                quater++;
                break;

            case (DIME):
                sum = sum + dimesInt;
                dime++;
                break;

            case (NICKEL):
                sum = sum + nickelsInt;
                nickel++;
                break;

            case (PENNY):
                sum = sum + penniesInt;
                penny++;
                break;
        }
    }

    // Calculating total number of coins used
    int total = quater + dime + nickel + penny;

    printf("Change recieved: %.2f\n", (float)sum / 100);
    printf("Quater(s): %i\n", quater);
    printf("Dime(s): %i\n", dime);
    printf("Nickel(s): %i\n", nickel);
    printf("Pennie(s): %i\n", penny);
    printf("Total coin(s) given: %i\n", total);
    printf("%i\n", total);

}