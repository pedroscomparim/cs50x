#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for their name
    string name = get_string("What's your name? ");

    // Greet the user by name
    printf("hello, %s\n", name);
}