#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

int stringLength(string s);

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
            printf("Invalid vote.\n");
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // if (candidates[i].name == name) doesnt work cause C compiler compares the addresses in
        // memory

        bool isSameName = true;

        /**
         * Iterates through all the chars in the current candidate name and compares it to the name
         * inputted to the function If it finds a different character, it sets isSameName to false
         * and breaks out of the inner loop If it doesn't find a different character, it adds 1 to
         * the current candidate votes and returns true
         */
        for (int j = 0; j < stringLength(candidates[i].name); j++)
        {
            if (candidates[i].name[j] != name[j])
            {
                isSameName = false;
                break;
            }
        }
        if (isSameName)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate mostVoted = candidates[0];

    // Finds the candidate with most votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > mostVoted.votes)
            mostVoted = candidates[i];
    }

    // Prints all the candidates with the same number of votes as the most voted candidate (tie
    // case)
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == mostVoted.votes)
            printf("%s\n", candidates[i].name);
    }

    return;
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
