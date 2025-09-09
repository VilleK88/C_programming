#include <stdio.h>
#include <stdbool.h>

bool read_positive(int *value);

int main()
{
    int count = 0;

    do {
        int value;
        const bool positive = read_positive(&value);
        if(positive)
        {
            const int sum = value * 2 + 20;
            printf("You didn't get it right. I have %d euros.\n", sum);
        }
        else {
            printf("Incorrect input\n");
            count++;
        }
    } while (count < 3);

    printf("I give up! See you later!\n");

    return 0;
}

bool read_positive(int *value)
{
    int num;

    printf("Guess how much money I have!\n");
    printf("Enter a positive number: ");

    if(scanf("%d", &num) != 1)
    {
        while(getchar() != '\n'){}
        return false;
    }

    if(num <= 0)
        return false;

    *value = num;
    return true;
}