#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int main(void)
{
    //Get text
    string text = get_string("Text: ");
    float letters = 0;
    float words = 1;
    float sentences = 0;
    
    //Count letters
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        if (isspace(text[i]))
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    //Calculate average
    float L = letters / words * 100;
    float S = sentences / words * 100;
    
    //Readability
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int result = round(index);
    
    //Output
    if (result >= 1 && result <= 16)
    {
            printf("Grade %i\n", result);
    }
    else
    {
        if (result < 1)
        {
            printf("Before Grade 1\n");
        }
        if (result > 16)
        {
            printf("Grade 16+\n");
        }
    }
}