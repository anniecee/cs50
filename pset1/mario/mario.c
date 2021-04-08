#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Prompt for pyramid height
    int height;
    do
    {
        height = get_int("Input height value (from 1 to 8): ");
    }
    while (height < 1 || height > 8);
    
    //Create pyramid
    int i;
    int s;
    int h;
    
    //Create rows
    for (i = 0; i < height; i++)
    {
        //Create space
        for (s = height - i; s > 1; s--) 
        {
            printf(" ");
        }
        //Create hash (left of pyramid)
        for (h = 0; h <= i; h++) 
        {
            printf("#");
        }
        //Create gap
        printf("  ");
        
        //Create hash (right of pyramid)
        for (h = 0; h <= i; h++) 
        {
            printf("#");
        }
        //Enter new line
        printf("\n");
    }
    
}