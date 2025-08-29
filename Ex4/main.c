#include <stdio.h>

int read_integer(void);
void handle_program(int this_count, float this_sum);

int main()
{
    int count = -1;
    float sum = 0;

    handle_program(count, sum);

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

void handle_program(int this_count, float this_sum) {
    int num = 0;

    while (num >= 0) {
        this_sum += (float)num;
        this_count++;
        num = read_integer();
    }

    float average = this_sum / this_count;
    printf("You entered %d positive numbers. The average is: %.3f\n", this_count, average);
}