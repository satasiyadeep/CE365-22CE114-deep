#include <iostream>
#include <string>
using namespace std;

class RDP {
private:
    string input;
    int pos;

    bool S();
    bool L();
    bool L_prime();

public:
    RDP(string str) : input(str), pos(0) {}
    bool parse();
};

bool RDP::S() {
    if (pos < input.length() && input[pos] == 'a') {
        pos++; // Match 'a'
        return true;
    }
    if (pos < input.length() && input[pos] == '(') {
        pos++; // Match '('
        if (L()) {
            if (pos < input.length() && input[pos] == ')') {
                pos++; // Match ')'
                return true;
            }
        }
    }
    return false;
}

bool RDP::L() {
    if (!S()) return false;
    return L_prime();
}

bool RDP::L_prime() {
    if (pos < input.length() && input[pos] == ',') {
        pos++; // Match ','
        if (!S()) return false;
        return L_prime();
    }
    return true; // Epsilon case
}

bool RDP::parse() {
    if (S() && pos == input.length()) {
        return true;
    }
    return false;
}

int main() {
    string test;
    cout << "Enter input string: ";
    cin >> test;
    
    RDP parser(test);
    cout << "Input: " << test << " -> " << (parser.parse() ? "Valid string" : "Invalid string") << endl;
    
    return 0;
}