#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Check if the input is one arguement only
    if (argc == 2)
    {
        //Check the value of argv, if not all digit, print Usage text
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // Convert key to int key
        int key = atoi(argv[1]);
        
        // Get plaintext
        string plaintext = get_string("plaintext: ");
        
        // Print ciphertext line
        printf("ciphertext: ");
        
        //Encrypt
        for (int i = 0, l = strlen(plaintext); i < l; i++)
        {
            //Check lowercase/uppercase and convert
            if (islower(plaintext[i]))
            {
                printf("%c", (((plaintext[i] + key) - 97) % 26) + 97);
            }
            else if (isupper(plaintext[i]))
            {
                printf("%c", (((plaintext[i] + key) - 65) % 26) + 65);
            }
                
            //If it's not letter, then print the original
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}