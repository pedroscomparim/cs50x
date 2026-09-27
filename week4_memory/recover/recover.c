#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];

    // JPEG file
    FILE *jpg = NULL;

    // Number of JPEGs found
    int file_number = 0;

    char filename[8];

    // Read the card block by block
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if this block starts a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already writing a JPEG, close it
            if (jpg != NULL)
            {
                fclose(jpg);
            }

            // Create filename: 000.jpg, 001.jpg, ...
            sprintf(filename, "%03i.jpg", file_number);

            jpg = fopen(filename, "w");

            file_number++;
        }

        // If currently inside a JPEG, write this block
        if (jpg != NULL)
        {
            fwrite(buffer, 1, 512, jpg);
        }
    }

    // Close final JPEG
    if (jpg != NULL)
    {
        fclose(jpg);
    }

    // Close memory card
    fclose(card);

    return 0;
}
