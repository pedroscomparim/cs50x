#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Start words_count at 1 to count the last (or only) word
    int letters_count = 0, words_count = 1, sentences_count = 0;

    string text = get_string("Text: ");

    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        // Count the three valid sentence terminators
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences_count++;
        }
        else if (text[i] == ' ')
        {
            words_count++;
        }
        else if (isalpha(text[i]))
        {
            letters_count++;
        }
    }

    float L = 100 * (float) letters_count / words_count;
    float S = 100 * (float) sentences_count / words_count;

    // Round the grade level to the nearest integer
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
