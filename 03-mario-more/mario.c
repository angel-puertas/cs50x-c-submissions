#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    while (height < 1 || height > 8)
    {
        height = get_int("Choose a height between 1 and 8: ");
    }

    for (int i = 0; i < height; i++)
    {
        // Print initial spaces
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }

        // Print first column
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // Print two spaces between columns
        printf("  ");

        // Print second column
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // Print new line
        printf("\n");
    }
}
