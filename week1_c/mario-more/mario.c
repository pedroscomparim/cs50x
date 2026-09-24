#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt for a height between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        // Left padding
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }

        // Left pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Gap between the pyramids
        printf("  ");

        // Right pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
