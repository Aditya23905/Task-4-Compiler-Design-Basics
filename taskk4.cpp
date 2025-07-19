#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <map>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
        default: return 0;
    }
}

int evaluate(string tokens) {
    stack<int> values;
    stack<char> ops;

    for (int i = 0; i < tokens.length(); i++) {
        if (tokens[i] == ' ') continue;

        // Number
        if (isdigit(tokens[i])) {
            int val = 0;
            while (i < tokens.length() && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            values.push(val);
            i--; // step back
        }

        // Opening brace
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

        // Closing brace
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop(); // remove '('
        }

        // Operator
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    string expr;
    cout << "Enter arithmetic expression: ";
    getline(cin, expr);

    try {
        int result = evaluate(expr);
        cout << "Result: " << result << endl;
    } catch (...) {
        cout << "Invalid expression!" << endl;
    }

    return 0;
}

