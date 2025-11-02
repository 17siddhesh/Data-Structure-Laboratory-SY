/*Write a program for managing customer service requests in a call center. Each request includes customer details (name, contact information) and service requirements. Utilize a queue data structure to efficiently handle incoming requests, ensuring they are processed in a first-comefirst-served manner. Implement functionalities to add new requests, process them sequentially, and track the status of ongoing requests. Consider the following initial customer service requests:  Request ID: 101  Customer Name: John Doe  Service Type: Technical Support Request ID: 102  Customer Name: Jane Smith  Service Type: Billing Inquiry Request ID: 103  Customer Name: David Brown  Service Type: Product Information*/
#include <iostream>
using namespace std;

struct Request {
    int requestID;
    char customerName[50];
    char serviceType[50];
};

struct Queue {
    Request arr[50];
    int front = -1;
    int rear = -1;

    bool isFull() {
        return rear == 49;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(Request r) {
        if (isFull()) {
            cout << "Queue full.\n";
            return;
        }
        if (front == -1)
            front = 0;
        rear++;
        arr[rear] = r;
        cout << "Added.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "No requests.\n";
            return;
        }
        cout << "Processing ID: " << arr[front].requestID 
             << " (" << arr[front].customerName << ")\n";
        front++;
    }

    void display() {
        if (isEmpty()) {
            cout << "No requests.\n";
            return;
        }
        cout << "\nPending:\n";
        for (int i = front; i <= rear; i++) {
            cout << "ID: " << arr[i].requestID
                 << ", " << arr[i].customerName
                 << ", " << arr[i].serviceType << "\n";
        }
    }
};

int main() {
    Queue q;

    // Initial Requests
    Request r1 = {101, "JohnDoe", "TechnicalSupport"};
    Request r2 = {102, "JaneSmith", "BillingInquiry"};
    Request r3 = {103, "DavidBrown", "ProductInfo"};
    q.enqueue(r1);
    q.enqueue(r2);
    q.enqueue(r3);

    int choice;
    do {
        cout << "\n--- Call Center ---\n";
        cout << "1. Add\n";
        cout << "2. Process\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Request newReq;
                cout << "ID: ";
                cin >> newReq.requestID;
                cout << "Name: ";
                cin >> newReq.customerName;  // no "one word" note
                cout << "Service: ";
                cin >> newReq.serviceType;   // no "one word" note
                q.enqueue(newReq);
                break;
            }

            case 2:
                q.dequeue();
                break;

            case 3:
                q.display();
                break;

            case 4:
                cout << "Exit.\n";
                break;

            default:
                cout << "Invalid.\n";
        }

    } while (choice != 4);

    return 0;
}
