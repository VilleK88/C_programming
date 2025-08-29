#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int handle_input(void);
void handle_menu(void);
void roll_dice(int max);

int main()
{
    srand(time(NULL)); // use current time as seed for random generator

    handle_menu();

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

void handle_menu(void)
{
    int choice = handle_input();
    while(1)
    {
        printf("Roll D6\nRoll D10\nQuit\n");
        int choice = handle_input();
        switch(choice)
        {
            case 1:
                roll_dice(6);
                break;
            case 2:
                roll_dice(10);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

void roll_dice(int max)
{
    printf("\n");
    int value = rand() % max + 1;
    printf("%d\n\n", value);
}