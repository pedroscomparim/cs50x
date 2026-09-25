#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];

    // Check that the key has only letters, and no repeated letters
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only letters.\n");
            return 1;
        }

        for (int j = i + 1; j < 26; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Key must not contain repeated letters.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // If it's a letter, substitute it using the key
        if (isalpha(plaintext[i]))
        {
            // Find its position from 0 to 25
            int index = tolower(plaintext[i]) - 'a';

            // Preserve the original letter's case
            if (isupper(plaintext[i]))
            {
                printf("%c", toupper(key[index]));
            }
            else
            {
                printf("%c", tolower(key[index]));
            }
        }
        // Non-letter characters (spaces, punctuation, digits) are printed unchanged
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}
