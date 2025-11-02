#include <iostream>
#include <string>
using namespace std;

// Structure for Student node
struct Student {
    int id;
    string name;
    string course;
    int age;
    Student* next;

    // Constructor
    Student(int i, string n, string c, int a) {
        id = i;
        name = n;
        course = c;
        age = a;
        next = NULL;
    }
};

// Hash table for storing student data
class StudentTable {
    static const int size = 10;
    Student* data[size];

    // Hash function
    int getIndex(int id) { 
        return id % size; 
    }

public:
    // Initialize all entries to NULL
    StudentTable() {
        for (int i = 0; i < size; i++)
            data[i] = NULL;
    }

    // Add a student record
    void addStudent(int id, string name, string course, int age) {
        int index = getIndex(id);
        Student* s = new Student(id, name, course, age);
        s->next = data[index];
        data[index] = s;
        cout << "\nStudent added successfully!\n";
    }

    // Search for a student by ID
    bool findStudent(int id) {
        int index = getIndex(id);
        Student* temp = data[index];
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "\nStudent Found!\n";
                cout << "ID: " << temp->id << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Course: " << temp->course << endl;
                cout << "Age: " << temp->age << endl;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Display all student records
    void showAllStudents() {
        bool any = false;
        for (int i = 0; i < size; i++) {
            if (data[i] != NULL) {
                any = true;
                cout << "\nIndex " << i << ":\n";
                Student* temp = data[i];
                while (temp != NULL) {
                    cout << "ID: " << temp->id 
                         << ", Name: " << temp->name
                         << ", Course: " << temp->course
                         << ", Age: " << temp->age << endl;
                    temp = temp->next;
                }
            }
        }
        if (!any)
            cout << "\nNo students added yet!\n";
    }
};

// Main program
int main() {
    StudentTable st;
    int choice;

    do {
        cout << "\nSTUDENT INFORMATION SYSTEM\n";
        cout << "1. Add New Student\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Show All Students\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {  // prevent infinite loop on invalid input
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 1) {
            int id, age;
            string name, course;
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Name : ";
            cin >> name;
            cout << "Enter Course : ";
            cin >> course;
            cout << "Enter Age: ";
            cin >> age;
            st.addStudent(id, name, course, age);
        } 
        else if (choice == 2) {
            int id;
            cout << "Enter Student ID to search: ";
            cin >> id;
            if (!st.findStudent(id))
                cout << "\nStudent not found!\n";
        } 
        else if (choice == 3) {
            st.showAllStudents();
        } 
        else if (choice == 4) {
            cout << "\nExiting the system. Goodbye!\n";
        } 
        else {
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
