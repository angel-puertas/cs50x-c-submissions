#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Credit card number: ");
    long number2 = number;

    int counter =
        1; // needs to start at 1 to be able to do modulo to find if the digit is even or odd
    int firstStep = 0;
    int secondStep = 0;

    while (number != 0)
    {
        int currentDigit = number % 10; // get last digit
        number /= 10;                   // removes last digit

        /**
         * FIRST STEP
         * Multiply every other digit by 2 starting with the number’s second-to-last digit
         * Then add those products’ digits together.
         */
        if (counter % 2 == 0) // we check for even because we start from the back with counter at 1
        {
            int doubledCurrentDigit = currentDigit * 2;
            if (doubledCurrentDigit >= 10)
            {
                while (doubledCurrentDigit != 0)
                {
                    firstStep += doubledCurrentDigit % 10;
                    doubledCurrentDigit /= 10;
                }
            }
            else
            {
                firstStep += doubledCurrentDigit;
            }
        }

        /**
         * SECOND STEP
         * Add the first step's sum to the sum of the digits that weren’t multiplied by 2.
         */
        if (counter % 2 != 0) // opposite as step 1 to get the rest of the numbers
        {
            secondStep += currentDigit;
        }

        counter++;
    }

    secondStep += firstStep;
    int lastDigit = secondStep % 10;

    /**
     * Get First and Second digits
     */
    int firstDigit;
    int secondDigit;
    for (int i = 1; i < counter; i++)
    {
        if (i == (counter - 2))
        {
            secondDigit = number2 % 10;
        }
        else if (i == (counter - 1))
        {
            firstDigit = number2 % 10;
        }
        number2 /= 10;
    }

    int length = counter - 1;

    /** AMEX */
    if (lastDigit == 0 && length == 15 &&
        ((firstDigit == 3 && secondDigit == 4) || (firstDigit == 3 && secondDigit == 7)))
    {
        printf("AMEX\n");
    }
    /** MASTERCARD */
    else if (lastDigit == 0 && length == 16 && firstDigit == 5 &&
             (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 ||
              secondDigit == 5))
    {
        printf("MASTERCARD\n");
    }
    /** VISA */
    else if (lastDigit == 0 && (length == 13 || length == 16) && firstDigit == 4)
    {
        printf("VISA\n");
    }
    /** INVALID */
    else
    {
        printf("INVALID\n");
    }
}
