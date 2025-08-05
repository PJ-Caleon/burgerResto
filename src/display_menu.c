#include <stdio.h>
#include "../include/display_menu.h"

// Define the menu items
MenuItem menuItems[MENU_SIZE] = {
    {"Burger", 47.00, 20},
    {"Cheese Burger", 50.00, 15},
    {"Egg Burger", 39.00, 20},
    {"Chili Burger", 53.00, 10},
    {"Cheesy Bacon", 65.00, 15},
    {"Chicken Burger", 39.00, 15},
    {"Longganisa Burger", 39.00, 15},
    {"Salad", 80.00, 15},
    {"Coke", 20.00, 15},
    {"Iced tea", 15.00, 15}
};

// Function to display menu
void display_menu(void) {
    printf("Menu:\n");
    printf("%-20s %-10s %-10s\n", "Item", "Price", "Stock");
    printf("---------------------------------------------\n");

    for (int i = 0; i < MENU_SIZE; i++) {
        printf("%-20s %-10.2f %-10d\n", menuItems[i].name, menuItems[i].price, menuItems[i].stock);
    }
}
