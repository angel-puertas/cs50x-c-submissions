#include <cs50.h>
#include <stdio.h>

int stringLength(string s);
char charToLower(char c);
int getPoints(string s);

int main(void)
{
    int player1Score = getPoints(get_string("Player 1: "));
    int player2Score = getPoints(get_string("Player 2: "));

    if (player1Score > player2Score)
        printf("Player 1 wins!");
    else if (player2Score > player1Score)
        printf("Player 2 wins!");
    else
        printf("Tie!");
}

/**
 * Iterates through the string adding 1 to the length variable in each iteration
 * until it finds the string terminator NUL character '\0' which signifies the end of the string
 */
int stringLength(string s)
{
    int length = 0;
    while (s[length] != '\0')
    {
        length++;
    }
    return length;
}

/**
 * Using ASCII table values, if the char is an uppercase (between 65 and 90 inclusive)
 * it adds 32 to the char to convert it to lowercase
 */
char charToLower(char c)
{
    if ((int) c >= 65 && (int) c <= 90)
    {
        c += 32;
    }
    return c;
}

int getPoints(string s)
{
    int const ALPHABET_LENGTH = 26;
    char alphabetArray[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int pointsArray[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                         1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int points = 0;

    /**
     * Iterates through the word, grabbing every char and finding its index in the alphabet array
     * then getting the corresponding value on the points array, and adding it to the points
     * variable
     */
    for (int i = 0; i < stringLength(s); i++)
    {
        char charFromInput = charToLower(s[i]);

        for (int j = 0; j <= ALPHABET_LENGTH; j++)
        {
            if (alphabetArray[j] == charFromInput)
            {
                points += pointsArray[j];
                break;
            }
        }
    }
    return points;
}
