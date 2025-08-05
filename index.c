#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

// ==============================
// Struct Definitions
// ==============================

#define MAX_ITEMS 10

struct MenuItem {
    char name[20];
    float price;
    int stock;
};

// ==============================
// Function Declarations
// ==============================

int login();
float takeOrder(struct MenuItem items[], int size, struct MenuItem orderedItems[], int *orderedItemCount);
void displayMenu(struct MenuItem items[], int size);
void generateReceipt(struct MenuItem items[], int size, float totalPrice);
char getch();

// ==============================
// Global Menu Items
// ==============================

struct MenuItem menuItems[MAX_ITEMS] = {
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

// ==============================
// Terminal-safe getch() function
// ==============================

char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// ==============================
// Login Function
// ==============================

int login() {
    #define MAX_USERS 10
    #define USERNAME 20
    #define PASSWORD 20

    typedef struct {
        char username[USERNAME];
        char password[PASSWORD];
    } User;

    User users[MAX_USERS] = {
        {"Allan", "Olivete"},
        {"Jaryl", "DeJesus"},
        {"PJ", ""},
        {"Vian", "Duran"},
        {"Zach", "DeGuzman"}
    };

    char username[USERNAME];
    char password[PASSWORD];
    int granted = 0;

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    int i = 0;
    char c;
    while (i < PASSWORD - 1) {
        c = getch();
        if (c == '\r' || c == '\n') break;
        password[i++] = c;
        printf("*");
    }
    password[i] = '\0';

    int found = 0;
    for (i = 0; i < MAX_USERS; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            printf("\nLogin successful!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nLogin failed. Please check your username and password.\n");
        granted = 0;
    } else {
        granted = 1;
    }

    return granted;
}

// ==============================
// Display Menu
// ==============================

void displayMenu(struct MenuItem items[], int size) {
    printf("\nMenu:\n");
    printf("%-20s %-10s %-10s\n", "Name", "Price (PHP)", "In Stock");
    printf("----------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-20s %-10.2f %-10d\n", items[i].name, items[i].price, items[i].stock);
    }
}

// ==============================
// Take Order
// ==============================

float takeOrder(struct MenuItem items[], int size, struct MenuItem orderedItems[], int *orderedItemCount) {
    float total = 0.0;
    char itemName[20];
    int quantity;
    *orderedItemCount = 0;

    printf("\nEnter your order (Type 'done' to finish):\n");
    while (1) {
        printf("\nItem name: ");
        scanf("%s", itemName);
        if (strcmp(itemName, "done") == 0)
            break;

        printf("Quantity: ");
        scanf("%d", &quantity);

        int found = 0;
        for (int i = 0; i < size; i++) {
            if (strcmp(itemName, items[i].name) == 0) {
                found = 1;
                if (items[i].stock >= quantity) {
                    total += items[i].price * quantity;
                    items[i].stock -= quantity;
                    printf("Added %d %s to your order.\n", quantity, itemName);

                    // Add to ordered items
                    strcpy(orderedItems[*orderedItemCount].name, items[i].name);
                    orderedItems[*orderedItemCount].price = items[i].price;
                    orderedItems[*orderedItemCount].stock = quantity;
                    (*orderedItemCount)++;
                } else {
                    printf("Sorry, insufficient stock for %s.\n", itemName);
                }
                break;
            }
        }

        if (!found) {
            printf("Item '%s' not found in the menu.\n", itemName);
        }
    }

    return total;
}

// ==============================
// Generate Receipt
// ==============================

void generateReceipt(struct MenuItem items[], int size, float totalPrice) {
    printf("\n------- RECEIPT -------\n");
    printf("%-20s %-10s %-10s %-10s\n", "Name", "Quantity", "Price", "Total");
    printf("----------------------------------------\n");

    float totalOrderPrice = 0.0;
    for (int i = 0; i < size; i++) {
        int quantityOrdered = items[i].stock;
        if (quantityOrdered > 0) {
            float itemTotal = quantityOrdered * items[i].price;
            printf("%-20s %-10d %-10.2f %-10.2f\n", items[i].name, quantityOrdered, items[i].price, itemTotal);
            totalOrderPrice += itemTotal;
        }
    }

    printf("----------------------------------------\n");
    printf("TOTAL ORDER PRICE: Php %.2f\n", totalOrderPrice);

    float discountedPrice = totalOrderPrice;
    char discountChoice;

    printf("\nDo you have a discount? (y/n): ");
    scanf(" %c", &discountChoice);
    if (discountChoice == 'y' || discountChoice == 'Y') {
        float discountPercentage;
        printf("Enter discount percentage: ");
        scanf("%f", &discountPercentage);
        discountedPrice -= (discountedPrice * (discountPercentage / 100));
        printf("Discounted Price: Php %.2f\n", discountedPrice);
    }

    float cashPaid;
    printf("\nEnter cash amount paid: ");
    scanf("%f", &cashPaid);
    float change = cashPaid - discountedPrice;
    if (change >= 0) {
        printf("Change: Php %.2f\n", change);
    } else {
        printf("Insufficient cash. Remaining balance: Php %.2f\n", -change);
    }
}

// ==============================
// Main Function
// ==============================

int main() {
    if (login() == 1) {
        int size = sizeof(menuItems) / sizeof(menuItems[0]);
        struct MenuItem orderedItems[MAX_ITEMS];
        int orderedItemCount;

        displayMenu(menuItems, size);

        float totalPrice = takeOrder(menuItems, size, orderedItems, &orderedItemCount);
        printf("\nTOTAL: Php %.2f\n", totalPrice);

        generateReceipt(orderedItems, orderedItemCount, totalPrice);
    }

    return 0;
}
