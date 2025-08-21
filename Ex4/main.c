#include <stdio.h>

int read_integer(void);

int main()
{
    int count = 0;
    float sum = 0;

    while(1)
    {
        int num = read_integer();
        if(num >= 0)
        {
            sum += (float)num;
            count++;
        }
        else
        {
            break;
        }
    }

    float average = sum / count;
    printf("You entered %d positive numbers. The average is: %.3f\n", count, average);

    return 0;
}

int read_integer(void)
{
    int value;
    printf("Enter positive numbers or negative to stop: ");
    if(scanf("%d", &value) != 1)
    {
        while(getchar() != '\n');
        printf("Invalid input\n");
        return 0;
    }
    return value;
}