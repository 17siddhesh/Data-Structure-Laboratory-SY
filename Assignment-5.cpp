/*Design an inventory management system for a warehouse where products are stored on racks and shelves. Each product is uniquely identified by a product ID and has attributes such as name, quantity, and price. Utilize a combination of arrays and pointers to efficiently manage the inventory. The system should allow for the addition of new products, updating of product quantities, and calculation of the total value of the inventory. Pointers should be employed to establish relationships between related products or track product movements within the warehouse. 1. Product ID: 101 - Name: Laptop - Quantity: 50 - Price: $800 2. Product ID: 102 - Name: Smartphone - Quantity: 100 - Price: $500 3. Product ID: 103 - Name: Tablet - Quantity: 30 - Price: $400 Implement functionalities to add new products with their respective attributes, update the quantities of existing products, and calculate the total value of the inventory based on the quantities and prices of the products. Utilize appropriate data structure to create connections between similar products or track the movement of products within the warehouse.*/
#include <iostream>
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    int quantity;
    float price;
    Product* next;
};

// Function to add  product
void addProduct(Product*& head, int id, string name, int quantity, float price) {
    Product* newProduct = new Product;
    newProduct->id = id;
    newProduct->name = name;
    newProduct->quantity = quantity;
    newProduct->price = price;
    newProduct->next = NULL;

    if (head == NULL) {
        head = newProduct;
    } else {
        Product* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newProduct;
    }

    cout << "Product added successfully.\n";
}

// Function to update quantity
void updateQuantity(Product* head, int id, int newQuantity) {
    Product* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->quantity = newQuantity;
            cout << "Quantity updated.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Product not found.\n";
}

// Function to calculate total inventory value
float calculateTotalValue(Product* head) {
    float total = 0;
    Product* temp = head;
    while (temp != NULL) {
        total = total + (temp->quantity * temp->price);
        temp = temp->next;
    }
    return total;
}

// Function to display all products
void displayProducts(Product* head) {
    if (head == NULL) {
        cout << "No products in inventory.\n";
        return;
    }
    Product* temp = head;
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << "  Name: " << temp->name
             << "  Quantity: " << temp->quantity
             << "  Price: " << temp->price << endl;
        temp = temp->next;
    }
}

int main() {
    Product* head = NULL;

    // given input
    addProduct(head, 101, "Laptop", 50, 800);
    addProduct(head, 102, "Smartphone", 100, 500);
    addProduct(head, 103, "Tablet", 30, 400);

    int choice;

    do {
        cout << "\n1. Display products\n";
        cout << "2. Add product\n";
        cout << "3. Update quantity\n";
        cout << "4. Calculate total inventory value\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts(head);
                break;

            case 2: {
                int id, quantity;
                float price;
                string name;
                cout << "Enter product ID: ";
                cin >> id;
                cout << "Enter product name: ";
                cin >> name;  // single word only
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter price: ";
                cin >> price;
                addProduct(head, id, name, quantity, price);
                break;
            }

            case 3: {
                int id, quantity;
                cout << "Enter product ID: ";
                cin >> id;
                cout << "Enter new quantity: ";
                cin >> quantity;
                updateQuantity(head, id, quantity);
                break;
            }

            case 4: {
                float total = calculateTotalValue(head);
                cout << "Total inventory value: " << total << endl;
                break;
            }

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
