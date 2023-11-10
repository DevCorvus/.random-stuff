#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

bool are_brackets_balanced(std::string input) {
    std::stack<char> stack;

    for (char c : input) {
        if (c == '{' || c == '[' || c == '(') {
            stack.push(c);
            continue;
        }

        if (stack.empty()) {
            return false;
        }

        char b = stack.top();

        if ((b == '{' && c == '}') || (b == '[' && c == ']') ||
            (b == '(' && c == ')')) {
            stack.pop();
        } else {
            return false;
        }
    }

    return stack.empty();
}

int main(void) {
    std::cout << are_brackets_balanced("((){}[{}{}])") << '\n';
    std::cout << are_brackets_balanced("((){}[{}{])") << '\n';
}
