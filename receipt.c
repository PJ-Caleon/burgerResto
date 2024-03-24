// Generate receipt
void generateReceipt(struct MenuItem items[], int size, float totalPrice) {
    printf("\n------- RECEIPT -------\n");
    printf("%-20s %-10s %-10s %-10s\n", "Name", "Quantity", "Price (PHP)", "Total (PHP)");
    printf("----------------------------------------\n");
  
    float totalOrderPrice = 0.0;
    for (int i = 0; i < size; i++) {
        if (items[i].stock < (menuItems[i].stock)) {
            int quantityOrdered = (menuItems[i].stock) - (items[i].stock);
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
