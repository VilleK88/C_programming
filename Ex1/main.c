#include <stdio.h>

float initialize_value(const char *text);
void handle_menu(float this_cash, float this_bus_ticket, float this_taxi_price);
float handle_payment(float current_cash, float price, const char *vehicle);

int main() 
{
    float cash, bus_ticket, taxi_price;

    bus_ticket = initialize_value("Enter price of bus ticket: ");
    taxi_price = initialize_value("Enter price of taxi: ");
    cash = initialize_value("How much money you have: ");

    handle_menu(cash, bus_ticket, taxi_price);

    return 0;
}

float initialize_value(const char *text) 
{
    float value;

    printf(text);
    scanf("%f", &value);

    return value;
}

void handle_menu(float this_cash, float this_bus_ticket, float this_taxi_price)
{
    while(this_cash >= this_bus_ticket || this_cash >= this_taxi_price) 
    {
        printf("Do you want to take\n");
        printf("1) bus (%.2f euros)\n", this_bus_ticket);
        printf("2) taxi (%.2f euros)\n", this_taxi_price);
        printf("Enter your selection: ");
        int choice;
        scanf("%d", &choice);
        switch(choice) 
        {
            case 1:
                this_cash = handle_payment(this_cash, this_bus_ticket, "bus");
                break;
            case 2:
                this_cash = handle_payment(this_cash, this_taxi_price, "taxi");
                break;
        }
    }

    printf("You need to walk. Bye\n");
}

float handle_payment(float current_cash, float price, const char *vehicle) 
{
    printf("You chose %s.\n", vehicle);

    if(current_cash >= price) 
    {
        current_cash -= price;
    }
    else 
    {
        printf("You don't have enough money for %s.\n", vehicle);
    }

    printf("You have %.2f euros left.\n", current_cash);

    return current_cash;
}