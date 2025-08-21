#include <stdio.h>

int handle_input(void);
void handle_roll_dice(void);
int read_range(int this_low, int this_high);

int main()
{
    handle_roll_dice();

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

void handle_roll_dice(void)
{
    int low = 1, high = 10, count = 0;

    printf("Let's play!\nRoll a die and enter your result.\n");

    while(count < 3)
    {
        int num = read_range(low, high);
        if(num != 6)
            printf("I got %d. I win!\n", num + 1);
        else
            printf("I got %d. It is a tie!\n", num);

        count++;
    }

    printf("Better luck next time. Bye!\n");
}

int read_range(int this_low, int this_high)
{
    int value;

    while(1)
    {
        printf("Enter a number between %d and %d: ", this_low, this_high);
        value = handle_input();
        printf("A number was successfully read.\n");
        if(value >= this_low && value <= this_high)
        {
            printf("The number is in the specified range.\n");
            break;
        }
    }

    return value;
}