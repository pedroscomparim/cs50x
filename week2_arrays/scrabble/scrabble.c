#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Point value of each letter, indexed from 'a' to 'z'
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_score(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = get_score(word1), score2 = get_score(word2);

    // Compare scores to decide the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Sum the point values of each letter in a word, ignoring non-letter characters
int get_score(string word)
{
    int len = strlen(word), score = 0;

    for (int i = 0; i < len; i++)
    {
        if (isalpha(word[i]))
        {
            // Normalize to lowercase so 'A' and 'a' score the same
            char letter = tolower(word[i]);
            score += POINTS[letter - 'a'];
        }
    }

    return score;
}
