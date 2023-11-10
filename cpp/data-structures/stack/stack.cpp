#include "stack.h"
#include <iostream>

int main(void) {
    auto stack = std::make_unique<Stack<unsigned int>>();

    stack->push(4);
    stack->push(1);
    stack->push(8);

    std::cout << "Size: " << stack->get_size() << '\n';
    std::cout << stack->pop() << '\n';
    std::cout << stack->pop() << '\n';
    std::cout << stack->pop() << '\n';
    std::cout << stack->pop() << '\n';
}
