#include <iostream>
#include "dictionary.h"
#include "stack.h"

using namespace std;

// Global variables
Dictionary
        variable;
struct Value {
    string
            name;
    Fraction
            num;
} value;
Stack<Value>
        numStack;
Stack<char>
        opStack;

bool hasPrecedence(char top, char input) {
    if (top == '*' || top == '/')
        return true;
    else if ((top == '+' || top == '-') && (input != '*' && input != '/'))
        return true;
    else
        return false;

}

void doOperator() {
    Value
        leftOperand, rightOperand, newValue;
    char
        op;

    newValue.name = "";
    newValue.num = 0;

    // pop from stack to correct variables
    // covert either side to fraction if needed
    rightOperand = numStack.pop();
    leftOperand = numStack.pop();
    op = opStack.pop();

    if (!rightOperand.name.empty())
        rightOperand.num = variable.search(rightOperand.name);
    if (op != '=' && !leftOperand.name.empty())
        leftOperand.num = variable.search(leftOperand.name);

    // check operator and do that operation
    if (op == '=') {
        variable.add(leftOperand.name, rightOperand.num);
        numStack.push(leftOperand);
    } else if (op == '*') {
        newValue.num = leftOperand.num * rightOperand.num;
        numStack.push(newValue);
    } else if (op == '/') {
        newValue.num = leftOperand.num / rightOperand.num;
        numStack.push(newValue);
    } else if (op == '+') {
        newValue.num = leftOperand.num + rightOperand.num;
        numStack.push(newValue);
    } else if (op == '-') {
        newValue.num = leftOperand.num - rightOperand.num;
        numStack.push(newValue);
    }
}

void evaluate(string s) {
    numStack.clear();
    opStack.clear();
    opStack.push('$');
    int first = 0;

    while (first < s.length()) {

        if (isdigit(s[first])) {
            value.name = "";
            value.num = 0;

            // convert digit sequence to fraction
            // store fraction in structure object and push onto numStack
            // advance "first" to first character past digit
            while (isdigit(s[first])) {
                value.num =  value.num * 10 + s[first] - '0';
                first++;
            }

            numStack.push(value);

        } else if (isalnum(s[first]) || s[first] == '_'){
            value.name = "";
            value.num = 0;

            // Extract name into string
            // Store name in structure and push onto numStack
            // advance "first" to first character past name
            while (isalnum(s[first])) {
                value.name += s[first];
                first++;
            }

            numStack.push(value);

        } else if (s[first] == '(') {
            // Push ( onto opStack
            // Increment "first"
            opStack.push('(');
            first++;

        } else if (s[first] == ')') {
            while (opStack.peek() != '(') {
                // perform top operation
                doOperator();
            }
            // Pop ( from top of opStack
            // Increment first
            opStack.pop();
            first++;

        } else if (s[first] == '*' || s[first] == '/' || s[first] == '+' || s[first] == '-' || s[first] == '=') {
            while (hasPrecedence(opStack.peek(), s[first])) {
                // Perform top operation
                doOperator();
            }
            // Push s[first] onto opStack
            // Increment first
            opStack.push(s[first]);
            first++;

        } else {
            // increment first
            first++;

        }
    }

    while (opStack.peek() != '$') {
        // preform top operation
        doOperator();
    }

    // output top of numStack
    if (numStack.peek().num == 0)
        cout << variable.search(numStack.peek().name) << endl;
    else
        cout << numStack.peek().num << endl;
}

int main() {
    string
        expression;

    // Take in expression and evaluate it
    while (getline(cin, expression)) {
        if (expression == "#")
            return 0;
        evaluate(expression);
    }
}
