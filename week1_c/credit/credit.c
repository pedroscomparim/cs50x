#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for the card number
    long credit_card = get_long("Number: ");

    long temp = credit_card;
    int sum = 0;
    int count = 0;
    long first_two_digits = credit_card;

    // Apply Luhn's algorithm and count the digits
    while (temp > 0)
    {
        int digit = temp % 10;
        count++;

        // Odd positions (1st, 3rd, 5th... from the right): add the digit as is
        if (count % 2 != 0)
        {
            sum += digit;
        }
        // Even positions (2nd, 4th, 6th... from the right): double the digit
        else
        {
            int product = digit * 2;

            // If the product has two digits (e.g. 6 * 2 = 12), add its digits (1 + 2)
            sum += (product % 10) + (product / 10);
        }

        temp = temp / 10;
    }

    // Extract the first two digits to identify the card brand
    while (first_two_digits >= 100)
    {
        first_two_digits /= 10;
    }
    int first_digit = first_two_digits / 10;

    // Reject numbers that fail Luhn's checksum
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    // Otherwise, check length and starting digits to identify the brand
    else if ((count == 15) && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if ((count == 16) && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 || count == 16) && (first_digit == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
