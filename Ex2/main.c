#include <stdio.h>

#define SIZE 12

float initialize_value(char *this_text);
void handle_income(float *tax, float *salary, float income_limit, float tax_rate,  float tax_rate_overl);
void handle_tax(float *this_salary, float *this_tax, float this_month_salary, float this_tax_rate);
void print_incomes(float *tax, float *salary);

int main() {
    float tax[SIZE], salary[SIZE];

    float tax_rate = initialize_value("Enter tax rate:");
    float income_limit = initialize_value("Enter income limit:");
    float tax_rate_overl = initialize_value("Enter tax rate for income over the limit:");

    handle_income(tax, salary, income_limit, tax_rate, tax_rate_overl);
    print_incomes(tax, salary);

    return 0;
}

float initialize_value(char *this_text)
{
    float value;

    printf("%s ", this_text);
    scanf("%f", &value);

    return value;
}

void handle_income(float *tax, float *salary, float income_limit, float tax_rate,  float tax_rate_overl)
{
    float total_income = 0;

    for(int i = 0; i < SIZE; i++) 
    {
        float month_salary;

        printf("Enter income for month %d: ", i + 1);
        scanf("%f", &month_salary);
        total_income += month_salary;

        if(total_income < income_limit)
            handle_tax(&salary[i], &tax[i], month_salary, tax_rate);
        else
            handle_tax(&salary[i], &tax[i], month_salary, tax_rate_overl);
    }
}

void handle_tax(float *this_salary, float *this_tax, float this_month_salary, float this_tax_rate)
{
    *this_salary = this_month_salary;
    this_month_salary *= (this_tax_rate / 100);
    *this_tax = this_month_salary;
}

void print_incomes(float *tax, float *salary)
{
    printf("month\tincome\t   tax\n");

    for (int i = 0; i < SIZE; i++) 
    {
        printf("%5d %8.2f %7.2f\n", i + 1, salary[i], tax[i]);
    }
}