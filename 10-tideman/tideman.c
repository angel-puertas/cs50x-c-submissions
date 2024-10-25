#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool isSkip(int loser, int winner);
int stringLength(string s);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
            locked[i][j] = false;
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        // if (candidates[i].name == name) doesnt work cause C compiler compares the addresses in
        // memory

        if (stringLength(name) != stringLength(candidates[i]))
            continue;

        bool isSameName = true;

        /**
         * Iterates through all the chars in the current candidate name and compares it to the name
         * inputted to the function If it finds a different character, it sets isSameName to false
         * and breaks out of the inner loop If it doesn't find a different character, it adds 1 to
         * the current candidate votes and returns true
         */
        for (int j = 0; j < stringLength(candidates[i]); j++)
        {
            if (candidates[i][j] != name[j])
            {
                isSameName = false;
                break;
            }
        }
        if (isSameName)
        {
            ranks[rank] = i; // index of the candidate for voter's rank "rank"
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO

    // rank[0] > rank[1] and rank[2]
    // rank[1] > rank[2]
    // rank[2]

    // 1st iter -> preferences[0][1]++ preferences[0][2]++ ...
    // 2nd iter -> preferences[1][2]++ preferences[1][3]++ ...
    // ...
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // preferences[i][j] and preferences[j][i]

            // 1. compare preferences[0][1] to preferences[1][0], preferences[0][2] to
            // preferences[2][0] ...
            // 2. compare preferences[1][2] to preferences[2][1], preferences[1][3] to
            // preferences[3][1] ...
            // 3. compare preferences[2][3] to preferences[3][2], preferences[2][4] to
            // preferences[4][2] ... there doesn't seem to be overlap...?

            if (preferences[i][j] > preferences[j][i])
            {
                pair newPair;
                newPair.winner = i;
                newPair.loser = j;
                pairs[pair_count] = newPair;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pair newPair;
                newPair.winner = j;
                newPair.loser = i;
                pairs[pair_count] = newPair;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    bool isSorted;
    do
    {
        isSorted = true;
        for (int i = 0; i < pair_count; i++)
        {
            int currentStrength = preferences[pairs[i].winner][pairs[i].loser] -
                                  preferences[pairs[i].loser][pairs[i].winner];
            int nextStrength = preferences[pairs[i + 1].winner][pairs[i + 1].loser] -
                               preferences[pairs[i + 1].loser][pairs[i + 1].winner];

            if (nextStrength > currentStrength)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;

                isSorted = false;
            }
        }
    }
    while (!isSorted);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // check in the locked array what edges go from the to-add loser
        // aka, see who loses against this future loser
        // recursively check the losers agains the current to-be loser
        // if any of these recursive checks end with the winner being the loser, skip

        // recursively checks if the loser of a loser wins over winner
        bool skip = isSkip(loser, winner);
        if (!skip)
            locked[winner][loser] = true;
    }
}

bool isSkip(int loser, int winner)
{
    if (locked[loser][winner])
        return true;
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[loser][i])
        {
            /**
             * used chatgpt to learn what was wrong with my recursive function, only made one
             * change:
             *
             * from:
             * isSkip(i, winner)
             *
             * to:
             * if (isSkip(i, winner)) return true;
             *
             * return value wasnt being propagated properly within the many recursion calls
             */
            if (isSkip(i, winner))
                return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    // there doesnt seem to be a mismatch between indexes from the locked array and the candidates
    // array...?

    /**
     * Checks if anyone is locked over the current candidate
     * If this is the case, turns is winner to false and breaks to the next outer loop to check next
     * candidate If this is not the case, outer loop naturally continues and prints current winner,
     * then continues checking in case there is a tie
     */
    for (int i = 0; i < candidate_count; i++)
    {
        bool isWinner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                isWinner = false;
                break;
            }
        }
        if (isWinner)
            printf("%s\n", candidates[i]);
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
