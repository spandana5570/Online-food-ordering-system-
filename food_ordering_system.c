
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for menu item
typedef struct MenuItem {
    int id;
    char name[50];
    float price;
    struct MenuItem* next;
} MenuItem;

// Structure for cart item
typedef struct CartItem {
    int id;
    char name[50];
    float price;
    int quantity;
    struct CartItem* next;
} CartItem;

MenuItem* menuHead = NULL;
CartItem* cartHead = NULL;

// Function to add item to menu
void addMenuItem(int id, char name[], float price) {
    MenuItem* newItem = (MenuItem*)malloc(sizeof(MenuItem));
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->next = NULL;

    if (menuHead == NULL) {
        menuHead = newItem;
    } else {
        MenuItem* temp = menuHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newItem;
    }
}

// Display the menu
void displayMenu() {
    MenuItem* temp = menuHead;
    printf("\n--- MENU ---\n");
    while (temp != NULL) {
        printf("ID: %d | %s | $%.2f\n", temp->id, temp->name, temp->price);
        temp = temp->next;
    }
}

// Add item to cart
void addToCart(int id, int quantity) {
    MenuItem* temp = menuHead;
    while (temp != NULL) {
        if (temp->id == id) {
            // Check if item already exists in cart
            CartItem* ctemp = cartHead;
            while (ctemp != NULL) {
                if (ctemp->id == id) {
                    ctemp->quantity += quantity;
                    printf("%s quantity updated in cart.\n", ctemp->name);
                    return;
                }
                ctemp = ctemp->next;
            }

            // If not in cart, add new
            CartItem* newCartItem = (CartItem*)malloc(sizeof(CartItem));
            newCartItem->id = temp->id;
            strcpy(newCartItem->name, temp->name);
            newCartItem->price = temp->price;
            newCartItem->quantity = quantity;
            newCartItem->next = NULL;

            if (cartHead == NULL) {
                cartHead = newCartItem;
            } else {
                CartItem* last = cartHead;
                while (last->next != NULL)
                    last = last->next;
                last->next = newCartItem;
            }
            printf("%s added to cart.\n", newCartItem->name);
            return;
        }
        temp = temp->next;
    }
    printf("Item ID not found in menu.\n");
}

// View cart
void viewCart() {
    if (cartHead == NULL) {
        printf("\nYour cart is empty.\n");
        return;
    }

    CartItem* temp = cartHead;
    printf("\n--- YOUR CART ---\n");
    while (temp != NULL) {
        printf("%s x %d = $%.2f\n", temp->name, temp->quantity, temp->price * temp->quantity);
        temp = temp->next;
    }
}

// Checkout and generate bill
void placeorder() {
    if (cartHead == NULL) {
        printf("\nYour cart is empty. Add items before placeorder.\n");
        return;
    }

    float total = 0;
    CartItem* temp = cartHead;
    printf("\n--- BILL ---\n");
    while (temp != NULL) {
        float cost = temp->price * temp->quantity;
        printf("%s x %d = $%.2f\n", temp->name, temp->quantity, cost);
        total += cost;
        temp = temp->next;
    }
    printf("Total Amount: $%.2f\n", total);

    // Clear cart after checkout
    while (cartHead != NULL) {
        CartItem* toFree = cartHead;
        cartHead = cartHead->next;
        free(toFree);
    }
    printf("Thank you for your order!\n");
}

// Main function
int main() {
    int choice, id, qty;

    // Predefined menu
    addMenuItem(1, "Burger", 5.99);
    addMenuItem(2, "Pizza", 8.99);
    addMenuItem(3, "Pasta", 7.49);
    addMenuItem(4, "Sandwich", 4.25);
    addMenuItem(5, "Fries", 2.99);

    do {
        printf("\n--- ONLINE FOOD ORDERING ---\n");
        printf("1. View Menu\n2. Add to Cart\n3. View Cart\n4. place order\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                displayMenu();
                printf("Enter Item ID and Quantity: ");
                scanf("%d%d", &id, &qty);
                addToCart(id, qty);
                break;
            case 3:
                viewCart();
                break;
            case 4:
                placeorder();
                break;
            case 5:
                printf("Exiting. Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}
