#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Get input
    float dollars;
    int cents;
    do 
    {
        dollars = get_float("Change owned: ");
        cents = round(dollars * 100);
    }
    while (dollars < 0);
    
    //Initialize number of coins
    int coins;
    coins = 0;
    
    //Count quarters
    while (cents >= 25)
    {
        cents = (cents - 25);
        coins++;
    }
    //Count dimes
    while (cents >= 10 && cents < 25)
    {
        cents = (cents - 10);
        coins++;
    }
    //Count nickles
    while (cents >= 5 && cents < 10)
    {
        cents = (cents - 5);
        coins++;
    }
    //Count pennies
    while (cents >= 1 && cents < 5) 
    { 
        cents = (cents - 1);
        coins++;
    }
    
    //Display output
    printf("Number of coins: %i\n", coins);
}
    
   

