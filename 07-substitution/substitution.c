#include <cs50.h>
#include <ctype.h> // for isdigit() method
#include <stdio.h>

char charToLower(char c);
int stringLength(string s);

int main(int argc, string argv[])
{
    /** Checks theres exactly one argument */
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                         'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    string key = argv[1];
    int keyLength = stringLength(key);

    /** Checks the length of the key is exactly 26 chars long */
    if (keyLength != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < keyLength; i++)
    {
        /** Formats key to uppercase because thats what the rest of the program expects */
        if ((int) key[i] >= 97 && (int) key[i] <= 122)
            key[i] -= 32;

        /** Checks all key chars are letters */
        if (!isalpha(key[i]))
            return 1;
    }

    /** Checks there arent repeated chars in the key */
    for (int i = 0; i < keyLength; i++)
    {
        int repeatedChars = 0;
        for (int j = 0; j < i; j++)
        {
            if (key[i] == key[j])
                repeatedChars++;
            if (repeatedChars == 1)
                return 1;
        }
    }

    string plaintext = get_string("plaintext: ");
    int plaintextLength = stringLength(plaintext);
    char ciphertext[plaintextLength];

    /**
     * 1. Get first letter of the plaintext
     * 2. Find its index in the alphabet array
     * 3. Add corresponding cypher index to cyphertext string
     */
    for (int i = 0; i <= plaintextLength; i++)
    {
        // If char is not a letter keep it as is
        if (!isalpha(plaintext[i]))
        {
            ciphertext[i] = plaintext[i];
            continue;
        }
        for (int j = 0; j <= 26; j++)
        {
            // Finds plaintext char on alphabet
            if (charToLower(plaintext[i]) == alphabet[j])
            {
                /**
                 * Checks if plaintext char is upper or lower
                 * If its upper, it gets the corresponding key char since it is already in upper
                 * If its lower, it gets the corresponding key char and converts it to lower since
                 * by default its in upper
                 */
                if ((int) plaintext[i] >= 65 && (int) plaintext[i] <= 90)
                    ciphertext[i] = key[j];
                else
                    ciphertext[i] = charToLower(key[j]);
            }
        }
    }

    printf("ciphertext: %s\n", ciphertext);
}

int stringLength(string s)
{
    int length = 0;
    while (s[length] != '\0')
    {
        length++;
    }
    return length;
}

char charToLower(char c)
{
    if ((int) c >= 65 && (int) c <= 90)
    {
        c += 32;
    }
    return c;
}
