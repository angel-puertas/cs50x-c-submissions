#include <cs50.h>
#include <stdio.h>

int stringLength(string s);
int averageWordLengthPerHundredWords(int letterCount, int wordCount);
int averageSentenceNumberPerHundredWords(int sentenceCount, int wordCount);

/**
 * Fails two tests:
 * handles more complex single sentence
 * handles questions in passage
 */
int main(void)
{
    string text = get_string("Enter text: ");
    int textLength = stringLength(text);

    int averageNumberOfLetters;

    int letterCount = 0;
    int wordCount = 1; // start at 1 to account final word which doesnt have a space
    int sentenceCount = 0;
    char previousChar = 'Z';
    for (int i = 0; i < textLength; i++)
    {
        // finding letters
        if (text[i] != ' ' && text[i] != '.')
            letterCount++;
        // finding words
        else if (text[i] == ' ')
            wordCount++;
        // finding sentences (for some reason the '?' case doesnt work)
        else if ((text[i] == '.' && previousChar != '.') || text[i] == '?')
            sentenceCount++;

        previousChar = text[i];
    }

    int L = averageWordLengthPerHundredWords(letterCount, wordCount);
    int S = averageSentenceNumberPerHundredWords(sentenceCount, wordCount);
    int index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 1 && index < 16)
        printf("Grade %i\n", index);
    else
        printf("Grade 16+\n");
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

int averageWordLengthPerHundredWords(int letterCount, int wordCount)
{
    // rule of three
    // a: wordCount - b: letterCount
    // c: 100 words - x: adjustedLetterCount
    // x = (b * c) / a
    // adjustedLetterCount = (letterCount * 100 words) / wordCount

    return (letterCount * 100) / wordCount;
}

int averageSentenceNumberPerHundredWords(int sentenceCount, int wordCount)
{
    // rule of three
    // a: wordCount - b: sentenceCount
    // c: 100 words - x: adjustedSentenceCount
    // x = (b * c) / a
    // adjustedLetterCount = (sentenceCount * 100 words) / wordCount

    return (sentenceCount * 100) / wordCount;
}
