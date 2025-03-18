#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

vector<Quadruple> quadruples;
int tempCount = 1;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string applyOp(string a, string b, char op) {
    string temp = "t" + to_string(tempCount++);
    quadruples.push_back({string(1, op), a, b, temp});
    return temp;
}


string evaluateExpression(string expression) {
    stack<string> values;
    stack<char> ops;
    stringstream ss(expression);
    char ch;

    while (ss >> ch) {
        if (isdigit(ch)) { 
            ss.putback(ch);
            string num;
            ss >> num;
            values.push(num);
        } else if (ch == '(') {
            ops.push(ch);
        } else if (ch == ')') {
            while (!ops.empty() && ops.top() != '(') {
                string val2 = values.top(); values.pop();
                string val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop();
        } else { 
            while (!ops.empty() && precedence(ops.top()) >= precedence(ch)) {
                string val2 = values.top(); values.pop();
                string val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(ch);
        }
    }

    while (!ops.empty()) {
        string val2 = values.top(); values.pop();
        string val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    string expression;
    cout << "Enter arithmetic expression: ";
    getline(cin, expression);

    evaluateExpression(expression);


    cout << "\nOperator | Operand 1 | Operand 2 | Result" << endl;
    for (auto &quad : quadruples) {
        cout << quad.op << "\t   | " << quad.arg1 << "\t  | " << quad.arg2 << "\t  | " << quad.result << endl;
    }

    return 0;
}