#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a product
struct Product
{
    char name[50];
    double price;
};

// Structure to represent an item in the cart
struct CartItem
{
    struct Product product;
    int quantity;
    struct CartItem *next;
};

// Global pointer to the cart
struct CartItem *cart = NULL;

// Sample product catalog
struct Product productCatalog[] = {
    {"Product A", 13.99},
    {"Product B", 7.99},
    {"Product C", 82.49},
    {"Product D", 55.99}};

// Function to display the product catalog
void display_catalog()
{
    printf("Product Catalog:\n");
    for (int i = 0; i < sizeof(productCatalog) / sizeof(productCatalog[0]); ++i)
    {
        printf("%d. %s - $%.2f\n", i + 1, productCatalog[i].name, productCatalog[i].price);
    }
}

// Function to add an item to the cart
void add_to_cart(int productIndex, int quantity)
{
    if (productIndex < 0 || productIndex >= sizeof(productCatalog) / sizeof(productCatalog[0]))
    {
        printf("Invalid product index.\n");
        return;
    }

    struct CartItem *newCartItem = (struct CartItem *)malloc(sizeof(struct CartItem));
    newCartItem->product = productCatalog[productIndex];
    newCartItem->quantity = quantity;
    newCartItem->next = cart;
    cart = newCartItem;

    printf("Added '%s' to cart.\n", productCatalog[productIndex].name);
}

// Function to display the cart
void display_cart()
{
    printf("Cart:\n");
    struct CartItem *current = cart;
    while (current != NULL)
    {
        printf("%s - Quantity: %d\n", current->product.name, current->quantity);
        current = current->next;
    }
}

// Function to calculate the total price of items in the cart
double calculate_total()
{
    double total = 0.0;
    struct CartItem *current = cart;
    while (current != NULL)
    {
        total += current->product.price * current->quantity;
        current = current->next;
    }
    return total;
}

int main()
{
    int choice, productIndex, quantity;

    do
    {
        printf("\nE-Commerce Product Catalog:\n");
        printf("1. Browse Products\n");
        printf("2. Add Product to Cart\n");
        printf("3. View Cart\n");
        printf("4. Proceed to Checkout\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_catalog();
            break;
        case 2:
            display_catalog();
            printf("Enter the product index to add: ");
            scanf("%d", &productIndex);
            printf("Enter the quantity: ");
            scanf("%d", &quantity);
            add_to_cart(productIndex - 1, quantity);
            break;
        case 3:
            display_cart();
            break;
        case 4:
            printf("Total: $%.2f\n", calculate_total());
            printf("Thank you for shopping!\n");
            break;
        case 5:
            printf("Exiting E-Commerce Product Catalog.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    // Free memory (in a real application, you would need to free the cart items)
    struct CartItem *current = cart;
    while (current != NULL)
    {
        struct CartItem *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
