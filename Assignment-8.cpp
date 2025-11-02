/*Implement a circular queue for managing customer orders in a drive-thru lane of a fast-food restaurant. Utilize the circular queue data structure to efficiently handle orders, ensuring fair processing and minimal waiting times. Implement functionalities to add new orders, process orders in a round-robin manner, and track the status of ongoing orders. Consider the following initial customer orders in the drive-thru lane: 1. Order ID: 101 - Items: Burger, Fries, Drink - Customer Name: Rahul Sharma 2. Order ID: 102 - Items: Chicken Sandwich, Salad, Drink - Customer Name: Priya Patel 3. Order ID: 103 - Items: Pizza, Wings, Drink - Customer Name: Aarav Gupta
*/
#include <iostream>
using namespace std;

struct Order {
    int orderID;
    char customerName[50];
    char items[100];
};

struct CircularQueue {
    Order arr[50];
    int front;
    int rear;
    int size;

    // Constructor to initialize values
    CircularQueue() {
        front = -1;
        rear = -1;
        size = 50;
    }

    bool isFull() {
        return (front == 0 && rear == size - 1) || (rear + 1 == front);
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(Order o) {
        if (isFull()) {
            cout << "Queue full.\n";
            return;
        }
        if (front == -1)
            front = 0;
        rear = (rear + 1) % size;
        arr[rear] = o;
        cout << "Order added.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "No orders to process.\n";
            return;
        }
        cout << "Processing ID: " << arr[front].orderID
             << " (" << arr[front].customerName << ")\n";
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % size;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "No orders.\n";
            return;
        }
        cout << "\nOrders in queue:\n";
        int i = front;
        while (true) {
            cout << "ID: " << arr[i].orderID
                 << ", " << arr[i].customerName
                 << ", " << arr[i].items << "\n";
            if (i == rear)
                break;
            i = (i + 1) % size;
        }
    }
};

int main() {
    CircularQueue q;

    // given inputs
    Order o1 = {101, "RahulSharma", "Burger,Fries,Drink"};
    Order o2 = {102, "PriyaPatel", "ChickenSandwich,Salad,Drink"};
    Order o3 = {103, "AaravGupta", "Pizza,Wings,Drink"};

    q.enqueue(o1);
    q.enqueue(o2);
    q.enqueue(o3);

    int choice;
    do {
        cout << "\n--- Drive-Thru Orders ---\n";
        cout << "1. Add Order\n";
        cout << "2. Process Order\n";
        cout << "3. Display Orders\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Order newOrder;
                cout << "Order ID: ";
                cin >> newOrder.orderID;
                cout << "Customer Name: ";
                cin >> newOrder.customerName;
                cout << "Items: ";
                cin >> newOrder.items;
                q.enqueue(newOrder);
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
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
