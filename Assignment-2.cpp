/*To write a program that reads daily temperature readings from a file named 'temperatures.txt', sorts them in ascending order using the Bubble Sort algorithm, displays the sorted list, and stores the sorted values in a new file named 'sorted_temperatures.txt'.*/
#include <iostream>
using namespace std;

// Bubble sort function
void bubbleSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int k = 0; k < n - i - 1; k++) {
            if (arr[k] > arr[k + 1]) {
                int temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of temperature readings: ";
    cin >> n;

    float temps[100];  // Array to store the temperatures
    cout << "Enter " << n << " temperatures:\n";
    for (int i = 0; i < n; i++) {
        cin >> temps[i];
    }

    // sort using bubble sort
    bubbleSort(temps, n);

    // display sorted temperatures
    cout << "\nSorted Temperatures (Ascending Order):\n";
    for (int i = 0; i < n; i++) {
        cout << temps[i] << " ";
    }
    cout << endl;

    return 0;
}
