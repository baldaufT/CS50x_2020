#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
    int diff;
}
pair;

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
bool circu(int over, int under);
void print_winner(void);

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
        {
            locked[i][j] = false;
        }
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
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(candidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            if(i < j){
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].diff = preferences[i][j];
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int currMaxV = 0;
    int currMax = 0;
    for(int i = 0; i < pair_count; i++){
        currMaxV = pairs[i].diff;
        currMax = i;
        for(int j = 0; j < pair_count; j++){
            if(pairs[j].diff > currMaxV){
                currMaxV = pairs[j].diff;
                currMax = j;
            }
        }
        pair help = pairs[i];
        pairs[i] = pairs[currMax];
        pairs[currMax] = help;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++){
        int over = pairs[i].winner;
        int under = pairs[i].loser;
        if(!circu(over, under)){
            locked[over][under] = true;
        }
    }
    return;
}

bool circu(int over, int under){
    if(over == under){
        return true;
    }
    for(int i = 0; i < candidate_count; i++){
        if(locked[under][i] == true){
            return circu(over, i);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool found = false;
    int ok = 0;
    for(int j = 0; j < candidate_count; j++){
        ok = j;
        found = false;
        for(int i = 0; i < candidate_count; i++){
            if(locked[i][j] == true){
                found = true;
                break;
            }

        }
        if(found == false){
            break;
        }
    }

    printf("%s\n", candidates[ok]);
    return;
}