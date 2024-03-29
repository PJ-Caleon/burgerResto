#include <stdio.h>

struct MenuItem {
    char name[20];
    float price;
    int stock;
};

struct MenuItem menuItems[] = {
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

void displayMenu(struct MenuItem items[], int size) {
    printf("Menu:\n");
    printf("%-20s %-10s %-10s\n", "Name", "Price (Php)", "In Stock");
    printf("----------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-20s %-10.2f %-10d\n", items[i].name, items[i].price, items[i].stock);
    }
}

float takeOrder(struct MenuItem items[], int size, struct MenuItem orderedItems[], int *orderedItemCount) {
    float total = 0.0;
    char itemName[20];
    int quantity;
    *orderedItemCount = 0; // Initialize the count of ordered items

    printf("----------------------------------------\n");
    printf("\nEnter your order (Type 'done' to finish):\n");
    while (1) {
        printf("\nItem name: ");
        scanf("%s", itemName);
        if (strcmp(itemName, "done") == 0)
            break;

        printf("Quantity: ");
        scanf("%d", &quantity);

        for (int i = 0; i < size; i++) {
            if (strcmp(itemName, items[i].name) == 0) {
                if (items[i].stock >= quantity) {
                    total += items[i].price * quantity;
                    items[i].stock -= quantity;
                    printf("Added %d %s to your order.\n", quantity, itemName);

                    // Store the ordered item and quantity
                    strcpy(orderedItems[*orderedItemCount].name, itemName);
                    orderedItems[*orderedItemCount].price = items[i].price;
                    orderedItems[*orderedItemCount].stock = quantity;
                    (*orderedItemCount)++;
                } else {
                    printf("Sorry, %s is out of stock or insufficient stock.\n", itemName);
                }
                break;
            }
        }
    }

    return total;
}

int main() {
    int size = sizeof(menuItems) / sizeof(menuItems[0]);
    struct MenuItem orderedItems[size]; // Array to store ordered items
    int orderedItemCount; // Variable to store the count of ordered items
    displayMenu(menuItems, size);
    float totalPrice = takeOrder(menuItems, size, orderedItems, &orderedItemCount);
    printf("\nTOTAL: \tPhp %.2f\n", totalPrice);
    return 0;
}
