#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>  // For malloc

#include "../include/take_order.h"  // Include the take_order.h header

uint32_t MAX_ORDER_LENGTH = 10;

// Function to take order, accepts menu as input
char* take_order(MenuItem menu[], int menu_size) {
    char orderItem[30];
    bool validOrder = false;

    // Dynamically allocate memory for the order
    char* order = malloc(MAX_ORDER_LENGTH * sizeof(char));  // Allocate memory for order
    if (order == NULL) {
        printf("Memory allocation failed\n");
        return NULL;  // Return NULL if allocation fails
    }

    printf("Enter your order (type 'done' to finish): ");
    while (1) {
        scanf(" %29[^\n]", orderItem);  // Read a string with spaces

        if (strcmp(orderItem, "done") == 0) {
            break;
        }

        // Check if the order item exists on the menu
        for (int i = 0; i < menu_size; i++) {
            if (strcmp(orderItem, menu[i].name) == 0) {
                // Valid order found, copy to order
                strcpy(order, orderItem);
                printf("You ordered: %s\n", order);
                validOrder = true;
                break;
            }
        }

        if (!validOrder) {
            printf("Invalid order, please try again: ");
        } else {
            validOrder = false;  // Reset for next iteration
        }
    }

    return order;  // Return the dynamically allocated memory
}
