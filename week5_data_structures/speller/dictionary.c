// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Dict size
unsigned int words_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *n = table[hash(word)];

    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *src = fopen(dictionary, "r");

    if (src == NULL)
        return false;

    char buffer[LENGTH + 2];

    while (fgets(buffer, sizeof(buffer), src) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        int h = hash(buffer);

        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            fclose(src);
            unload();
            return false;
        }

        strcpy(n->word, buffer);

        n->next = table[h];
        table[h] = n;

        words_count++;
    }

    fclose(src);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *next = n->next;
            free(n);
            n = next;
        }
    }
    return true;
}
