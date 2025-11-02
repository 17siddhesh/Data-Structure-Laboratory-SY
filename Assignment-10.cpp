#include <iostream>
#include <string>
using namespace std;

// Contact structure
struct Contact {
    int id;
    string name;
    string phone;
    string email;
};

// AVL tree node
struct Node {
    Contact info;
    Node* left;
    Node* right;
    int height;
};

// Get height of a node
int getHeight(Node* n) {
    return (n == NULL) ? 0 : n->height;
}

// Return maximum of two integers
int getMax(int a, int b) {
    return (a > b) ? a : b;
}

// Create new AVL node
Node* createNode(Contact newContact) {
    Node* node = new Node;
    node->info = newContact;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Get balance factor
int getBalance(Node* n) {
    return (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
}

// Add a contact
Node* addContact(Node* root, Contact newContact) {
    if (root == NULL)
        return createNode(newContact);

    if (newContact.name < root->info.name)
        root->left = addContact(root->left, newContact);
    else if (newContact.name > root->info.name)
        root->right = addContact(root->right, newContact);
    else {
        cout << "A contact with the same name already exists!\n";
        return root;
    }

    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && newContact.name < root->left->info.name)
        return rotateRight(root);
    if (balance < -1 && newContact.name > root->right->info.name)
        return rotateLeft(root);
    if (balance > 1 && newContact.name > root->left->info.name) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && newContact.name < root->right->info.name) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Display contacts in-order
void showContacts(Node* root) {
    if (!root) return;
    showContacts(root->left);
    cout << "\nContact ID: " << root->info.id;
    cout << "\nName: " << root->info.name;
    cout << "\nPhone: " << root->info.phone;
    cout << "\nEmail: " << root->info.email << "\n";
    showContacts(root->right);
}

// Search by name
Node* searchByName(Node* root, string searchName) {
    if (!root) return NULL;
    if (searchName == root->info.name) return root;
    else if (searchName < root->info.name) return searchByName(root->left, searchName);
    else return searchByName(root->right, searchName);
}

// Update contact
void updateContact(Node* root) {
    cin.ignore();
    string searchName;
    cout << "Enter the name of the contact to update: ";
    getline(cin, searchName);

    Node* target = searchByName(root, searchName);
    if (!target) {
        cout << "No contact found with that name.\n";
        return;
    }

    cout << "Current phone: " << target->info.phone << "\n";
    cout << "Current email: " << target->info.email << "\n";

    cout << "Enter new phone: ";
    getline(cin, target->info.phone);
    cout << "Enter new email: ";
    getline(cin, target->info.email);

    cout << "Contact details updated successfully.\n";
}

// Display menu
void showMenu() {
    cout << "\n--- CONTACT MANAGER ---\n";
    cout << "1. Add New Contact\n";
    cout << "2. Display All Contacts\n";
    cout << "3. Search Contact by Name\n";
    cout << "4. Update Contact Info\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    Node* root = NULL;
    int choice;
    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            Contact newContact;
            cout << "Enter Contact ID: ";
            cin >> newContact.id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, newContact.name);
            cout << "Enter Phone: ";
            getline(cin, newContact.phone);
            cout << "Enter Email: ";
            getline(cin, newContact.email);

            root = addContact(root, newContact);
            cout << "Contact added.\n";
        }
        else if (choice == 2) {
            if (!root) cout << "No contacts to display.\n";
            else {
                cout << "\nAll Contacts:\n";
                showContacts(root);
            }
        }
        else if (choice == 3) {
            cin.ignore();
            string searchName;
            cout << "Enter Name to search: ";
            getline(cin, searchName);

            Node* result = searchByName(root, searchName);
            if (result) {
                cout << "\nContact Found:\n";
                cout << "ID: " << result->info.id << "\n";
                cout << "Phone: " << result->info.phone << "\n";
                cout << "Email: " << result->info.email << "\n";
            } else cout << "No contact with that name found.\n";
        }
        else if (choice == 4) {
            if (!root) cout << "No contacts to update.\n";
            else updateContact(root);
        }
        else if (choice == 5) {
            cout << "Exiting Contact Manager. Goodbye!\n";
        }
        else cout << "Invalid choice. Try again.\n";

    } while (choice != 5);

    return 0;
}
