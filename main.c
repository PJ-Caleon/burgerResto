#include <stdio.h>
#include "../include/take_order.h"
#include "../include/display_menu.h"

char* order;

int main() {
    extern MenuItem menuItems[MENU_SIZE]; 

    display_menu(); 
    order = take_order(menuItems, MENU_SIZE); 
    printf("Final order: %s\n", order);

    return 0;
}
