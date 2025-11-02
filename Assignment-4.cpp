/*Imagine you are developing a system to manage student grades in a school. The grades are stored in a matrix where rows represent students, and columns represent subjects. However, most students do not take all subjects, resulting in a sparse matrix where most elements are zero. Given the sparse matrix representing student grades below, implement a solution using arrays to efficiently manage and manipulate the grades data: Perform operations such as calculating the average grade for each subject, id.*/
#include <iostream>
using namespace std;

struct Element {
    int row;
    int col;
    int value;
};

int main() {
    int students, subjects;
    cout << "Enter number of students (rows): ";
    cin >> students;
    cout << "Enter number of subjects (columns): ";
    cin >> subjects;

    int matrix[50][50];//matrix initialization with size.
    //taking input from user
    cout << "--- Enter Grades (enter 0 if subject not chosen) ---\n";
    for (int i = 0; i < students; i++) {
        for (int j = 0; j < subjects; j++) {
            cout << "Enter grade for student " << i + 1 
                 << ", subject " << j + 1 << ": ";
            cin >> matrix[i][j];
        }
    }

    // Displaying full matrix
    cout << "\nFull Grade Matrix:\n";
    for (int i = 0; i < students; i++) {
        for (int j = 0; j < subjects; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Converting to sparse matrix
    Element sparse[100];// as structure used is named element.
    int k = 0;
    for (int i = 0; i < students; i++) {
        for (int j = 0; j < subjects; j++) {
            if (matrix[i][j] != 0) {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }

    // Displaying sparse matrix
    cout << "\nSparse Matrix Representation :\n";//row column and value
    for (int i = 0; i < k; i++) {
        cout << sparse[i].row << " " 
             << sparse[i].col << " " 
             << sparse[i].value << endl;
    }

    // Calculating average grade for each subject
    cout << "\nAverage grade for each subject:\n";
    for (int j = 0; j < subjects; j++) {
        int sum = 0;
        int count = 0;
        for (int i = 0; i < k; i++) {
            if (sparse[i].col == j) {
                sum += sparse[i].value;
                count++;
            }
        }
        if (count > 0)
            cout << "Subject " << j + 1 << ": " << (sum / (float)count) << endl;
        else
            cout << "Subject " << j + 1 << ": No grades\n";
    }

    return 0;
}
