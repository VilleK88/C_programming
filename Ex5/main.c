#include <stdio.h>

int handle_input(void);
void handle_loop(int *this_count, int *this_low, int *this_high);
int read_range(int *this_low, int *this_high);

int main()
{
    int low = 1, high = 10, count = 0;

    printf("Let's play!\nRoll a die and enter your result.\n");
    handle_loop(&count, &low, &high);
    printf("Better luck next time. Bye!\n");
    
    return 0;
}

int handle_input(void)
{
    int value;

    if(scanf("%d", &value) != 1)
    {
        while(getchar() != '\n');
        printf("Invalid input.\n");
        return 0;
    }

    return value;
}

void handle_loop(int *this_count, int *this_low, int *this_high)
{
    while(*this_count < 3)
    {
        int num = read_range(this_low, this_high);
        if(num != 6)
            printf("I got %d. I win!\n", num + 1);
        else
            printf("I got %d. It is a tie!\n", num);

        (*this_count)++;
    }
}

int read_range(int *this_low, int *this_high)
{
    int value;

    do {
        printf("Enter a number between %d and %d: ", (*this_low), (*this_high));
        value = handle_input();
        if (value < *this_low || value > *this_high)
            printf("Number was outside the specified range. Try again.\n");
    } while (value < *this_low || value > *this_high);

    return value;
}