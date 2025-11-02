/*Write a program to perform a linear search for finding a specific contact in a phone book and return the contact's details.*/
#include <iostream>
#include <string>
using namespace std;
struct Contact {
    string name;
    string phone;
};
// Function to insert contacts
void insertContacts(Contact contacts[], int &size) {
    int n;
    cout << "How many contacts do you want to insert? " << endl;
    cin >> n;
    cin.ignore(); // we need to use ignore because of getline function
    for (int i = 0; i < n; i++) {
        cout << "Enter details for contact " << (size + 1) << endl;
        cout << "Name: ";
        getline(cin, contacts[size].name);
//using getline as we need to take the entire name. for example: Siddhesh Patil ,here the spacing will be ignored and the entire line will be taken as input.
        cout << "Phone: ";
        getline(cin, contacts[size].phone);
        size++;
    }
}

// Function to search contacts
void searchContact(Contact contacts[], int size) {
    string searchName;
    cout << "Enter the name to search: ";
    getline(cin, searchName);//again same as mentioned above

    for (int i = 0; i < size; i++) {
        if (contacts[i].name == searchName) {
            cout << "\nContact Found ”<< endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Phone: " << contacts[i].phone << endl;
            return;  // to exit function
        }
    }
    cout << "Contact not found in phone book." << endl;
}

int main() {
    Contact contacts[100];
    int size = 0;
    int choice;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Insert Contact" << endl;
        cout << "2. Search Contact" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // again because of getline we need to use ignore here.

        switch (choice) {
            case 1:
                insertContacts(contacts, size);
                break;
            case 2:
                searchContact(contacts, size);
                break;
            case 3:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid Choice" << endl;
        }
    }
}
