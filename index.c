#include <stdio.h>
#include <string.h>
int login();
float takeOrder();
void menuDisplay();

//login
int login() {
    //defiing lenght
    #define MAX_USERS 10
    #define USERNAME 20
    #define PASSWORD 20

    //defining boolean for access granted
    typedef int bool;
    bool granted;

    //structure to store variable
    typedef struct {
        char username[USERNAME];
        char password[PASSWORD];
    } User;

    //list of acceptable usernames and password
    User users[MAX_USERS] = {
        {"Allan", "Olivete"},
        {"Jaryl", "DeJesus"},
        {"PJ", " "},
        {"Vian","Duran"},
        {"Zach","DeGuzman"}
    };

    //initialize variables
    char username[USERNAME];
    char password[PASSWORD];

    //input of username
    printf("Enter username: ");
    scanf("%s", username);

    //input of password and outputting **** in terminal 
    printf("Enter password: ");
    int i = 0;
    char c;
    while (i < PASSWORD - 1) {
        c = getch();
        if (c == '\r' || c == '\n') {
            break;
        }
        password[i++] = c;
        printf("*");
    }
    password[i] = '\0'; // Null-terminate the password string

    //compares input username and password if matching or not
    int found = 0;
    for (i = 0; i < MAX_USERS; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("\nLogin successful!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        //if username and password does not match, do not give access for further functions
        printf("\nLogin failed. Please check your username and password.\n");
        granted = 0;
    }
    else{
        //if username and password match, give access for further functions
        granted = 1;
    }
    return granted;
}

//menu display
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
    printf("%-20s %-10s %-10s\n", "Name", "Price (PHP)", "In Stock");
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

// Generate receipt
void generateReceipt(struct MenuItem items[], int size, float totalPrice) {
    printf("\n------- RECEIPT -------\n");
    printf("%-20s %-10s %-10s %-10s\n", "Name", "Quantity", "Price (PHP)", "Total (PHP)");
    printf("----------------------------------------\n");

    float totalOrderPrice = 0.0;
    for (int i = 0; i < size; i++) {
        if (items[i].stock > 0) { // Check if the item was ordered (stock is positive)
            int quantityOrdered = items[i].stock;
            float itemTotal = quantityOrdered * items[i].price;

            printf("%-20s %-10d %-10.2f %-10.2f\n", items[i].name, quantityOrdered, items[i].price, itemTotal);
            totalOrderPrice += itemTotal;
        }
    }


    printf("----------------------------------------\n");
    printf("TOTAL ORDER PRICE: Php %.2f\n", totalOrderPrice);
  
    // Option for discounts
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


  
    // Option for cash payment
    float cashPaid;
  
    printf("\nEnter cash amount paid: ");
    scanf("%f", &cashPaid);
    float change = cashPaid - discountedPrice;
    if (change >= 0) {
        printf("Change: Php %.2f\n", change);
    } else {
        printf("Insufficient cash paid. Remaining balance: Php %.2f\n", -change);
    }
}

void main(){
    int key = login();
    if(key == 1){
        int size = sizeof(menuItems) / sizeof(menuItems[0]);
        struct MenuItem orderedItems[size]; // Array to store ordered items
        int orderedItemCount; // Variable to store the count of ordered items
        displayMenu(menuItems, size);
        float totalPrice = takeOrder(menuItems, size, orderedItems, &orderedItemCount);
        printf("\nTOTAL: \tPhp %.2f\n", totalPrice);

        //call out receipt.c
        generateReceipt(orderedItems, orderedItemCount, totalPrice);
    }    
}
