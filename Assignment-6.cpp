/*Write a program to convert infix expressions to postfix and prefix notation using stacks. Given
an infix expression as input, the system should efficiently convert it to postfix and prefix
notations, considering operator precedence and parentheses. Implement functionalities to handle
operators, operands, and parentheses while ensuring correct expression conversion.*/
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

#include <iostream>
#include <string>
using namespace std;

struct Stack {
    int topChar;
    int topStr;
    char opArr[100];
    string strArr[100];

    Stack() { topChar = -1; topStr = -1; }

    // Char stack
    void push(char c) { opArr[++topChar] = c; }
    char pop() { return opArr[topChar--]; }
    char peek() { return opArr[topChar]; }
    bool isEmpty() { return topChar == -1; }

    // String stack
    void push(string s) { strArr[++topStr] = s; }
    string popStr() { return strArr[topStr--]; }
    string peekStr() { return strArr[topStr]; }
    bool isEmptyStr() { return topStr == -1; }
};

// Precedence and operator check
int precedence(char c) {
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    if(c=='^') return 3;
    return 0;
}

bool isOperator(char c) {
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
}

// Infix to Postfix
string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";

    for(int i=0;i<(int)infix.length();i++){
        char c = infix[i];

        if((c>='0' && c<='9') || (c>='A' && c<='Z') || (c>='a' && c<='z')){
            postfix += c;
        }
        else if(c=='('){
            s.push(c);
        }
        else if(c==')'){
            while(!s.isEmpty() && s.peek()!='(') postfix += s.pop();
            s.pop(); // remove '('
        }
        else if(isOperator(c)){
            while(!s.isEmpty() && precedence(s.peek())>=precedence(c) && s.peek()!='(')
                postfix += s.pop();
            s.push(c);
        }
    }

    while(!s.isEmpty()) postfix += s.pop();

    return postfix;
}

// Infix to Prefix
string infixToPrefix(string infix) {
    Stack s;
    for(int i=0;i<(int)infix.length();i++){
        char c = infix[i];

        if((c>='0' && c<='9') || (c>='A' && c<='Z') || (c>='a' && c<='z')){
            string temp = "";
            temp += c;
            s.push(temp);
        }
        else if(c=='('){
            s.push(c);
        }
        else if(c==')'){
            while(!s.isEmpty() && s.peek()!='('){
                string a = s.popStr();
                string b = s.popStr();
                string operatorChar(1, s.pop());
                string temp = operatorChar + b + a;
                s.push(temp);
            }
            s.pop();
        }
        else if(isOperator(c)){
            while(!s.isEmpty() && precedence(s.peek())>=precedence(c) && s.peek()!='('){
                string a = s.popStr();
                string b = s.popStr();
                string operatorChar(1, s.pop());
                string temp = operatorChar + b + a;
                s.push(temp);
            }
            s.push(c);
        }
    }

    while(!s.isEmpty()){
        string a = s.popStr();
        string b = s.popStr();
        string operatorChar(1, s.pop());
        string temp = operatorChar + b + a;
        s.push(temp);
    }

    return s.popStr();
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    return 0;
}



