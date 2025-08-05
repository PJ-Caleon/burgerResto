#ifndef DISPLAY_MENU_H
#define DISPLAY_MENU_H

#define MENU_SIZE 10

// Define the structure for the menu items
typedef struct {
    char name[30];
    float price;
    int stock;
} MenuItem;

// Declare the function to display the menu
void display_menu(void);

#endif
