#include <stdio.h>
#include <stdbool.h>

int handle_input();
bool read_positive(const int *value);

int main()
{
    int count = 0;

    do {
        const int num = handle_input();
        if(num != -1)
        {
            const int sum = num * 2 + 20;
            printf("You didn't get it right. I have %d euros.\n", sum);
        }
        else count++;
    } while (count < 3);

    printf("I give up! See you later!\n");

    return 0;
}

int handle_input()
{
    int value;
    
    printf("Guess how much money I have!\n");
    printf("Enter a positive number: ");

    if(scanf("%d", &value) != 1)
    {
        while(getchar() != '\n');
        printf("Incorrect input.\n");
        value = -1;
    }
    else
    {
        bool positive = read_positive(&value);
        if(!positive)
        {
            printf("Incorrect input.\n");
            value = -1;
        }
    }

    return value;
}

bool read_positive(const int *value)
{
    if(*value < 0)
        return false;

    return true;
}