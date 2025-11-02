/*Write a program to convert infix expressions to postfix and prefix notation using stacks. Given an infix expression as input, the system should efficiently convert it to postfix and prefix notations, considering operator precedence and parentheses. Implement functionalities to handle operators, operands, and parentheses while ensuring correct expression conversion.*/
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



