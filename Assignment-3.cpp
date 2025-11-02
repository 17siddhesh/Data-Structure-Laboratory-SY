/*In a hospital management system, there's a requirement to maintain a record of patients waiting in the emergency room. Implement a singly linked list to manage this queue efficiently. The system should allow receptionists to add patients to the end of the queue, doctors to remove patients from the front of the queue for examination, and nurses to move patients up in priority if their condition deteriorates. Additionally, the system should provide functionality to display the current queue, search for specific patients, and update patient information as needed. The goal is to streamline the patient management process, ensuring timely and efficient care delivery in the emergency room.*/
#include <iostream>
using namespace std;
struct Patient {
    int id;
    char name[50];
    Patient* next;
};
Patient* front = NULL;
Patient* last = NULL; 
// Adding a patient to the end of the queue which is the receptionist's work as per the problem statement.
void addPatient() {
    Patient* newPatient = new Patient;
    cout << "Enter patient ID: ";
    cin >> newPatient->id;
    cout << "Enter patient name: ";
    cin >> newPatient->name;
    newPatient->next = NULL;

    if (last == NULL) {
        front = last = newPatient;
    } else {
        last->next = newPatient;
        last = newPatient;
    }
    cout << "Patient added to queue.\n";
}

// to remove a patient from the front(done by the doctor)
void removePatient() {
    if (front == NULL) {
        cout << "No patients in queue.\n";
        return;
    }
    Patient* temp = front;
    cout << "Patient removed: " << temp->id << " " << temp->name << endl;
    front = front->next;
    if (front == NULL) last = NULL;
    delete temp;
}

// now to move a patient up  in priority(done by the nurse)
void prioritizePatient() {
    if (front == NULL || front->next == NULL) {
        cout << "Not enough patients to prioritize.\n";
        return;
    }

    int pid;
    cout << "Enter patient ID to prioritize: ";
    cin >> pid;

    Patient* prev = NULL;
    Patient* curr = front;

    while (curr != NULL && curr->id != pid) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "Patient not found.\n";
        return;
    }

    if (curr == front) {
        cout << "Patient is already at front.\n";
        return;
    }

    if (curr == last) last = prev;
    prev->next = curr->next;

    curr->next = front;
    front = curr;

    cout << "Patient " << pid << " moved to front of queue.\n";
}

// Display queue
void displayQueue() {
    if (front == NULL) {
        cout << "Queue is empty.\n";
        return;
    }
    Patient* temp = front;
    cout << "Current Queue:\n";
    while (temp != NULL) {
        cout << temp->id << " " << temp->name << endl;
        temp = temp->next;
    }
}

// Search for patient
void searchPatient() {
    if (front == NULL) {
        cout << "Queue is empty.\n";
        return;
    }
    int pid;
    cout << "Enter patient ID to search: ";
    cin >> pid;

    Patient* temp = front;
    while (temp != NULL) {
        if (temp->id == pid) {
            cout << "Patient found: " << temp->id << " " << temp->name << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Patient not found.\n";
}

// Update patient info
void updatePatient() {
    if (front == NULL) {
        cout << "Queue is empty.\n";
        return;
    }
    int pid;
    cout << "Enter patient ID to update: ";
    cin >> pid;

    Patient* temp = front;
    while (temp != NULL) {
        if (temp->id == pid) {
            cout << "Enter new name: ";
            cin >> temp->name;
            cout << "Patient info updated.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Patient not found.\n";
}

int main() {
    int choice;
    do {
        cout << "--- Hospital Queue Management ---";
        cout << "1. Add Patient\n";
        cout << "2. Remove Patient\n";
        cout << "3. Prioritize Patient\n";
        cout << "4. Display Queue\n";
        cout << "5. Search Patient\n";
        cout << "6. Update Patient Info\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: removePatient(); break;
            case 3: prioritizePatient(); break;
            case 4: displayQueue(); break;
            case 5: searchPatient(); break;
            case 6: updatePatient(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
