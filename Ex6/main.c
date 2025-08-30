#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int handle_input(void);
void menu_info(void);
void roll_dice(int max);

int main()
{
    int choice = 0;
    srand(time(NULL));

    do {
        menu_info();
        choice = handle_input();
        switch(choice) {
            case 1:
                roll_dice(6);
                break;
            case 2:
                roll_dice(10);
                break;
            case 3:
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 3);

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

void menu_info(void)
{
    printf("1) Roll D6\n2) Roll D10\n3) Quit\n");
    printf("Input value: ");
}

void roll_dice(int max)
{
    printf("\n");
    int value = rand() % max + 1;
    printf("%d\n\n", value);
}