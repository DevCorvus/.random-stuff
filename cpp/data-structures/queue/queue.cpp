#include "queue.h"
#include <iostream>
#include <memory>

int main(void) {
    auto queue = std::make_unique<Queue<unsigned int>>();

    queue->enqueue(4);
    queue->enqueue(1);
    queue->enqueue(8);

    std::cout << "Size: " << queue->get_size() << '\n';
    std::cout << "Peek: " << queue->peek() << '\n';
    std::cout << queue->dequeue() << '\n';
    std::cout << queue->dequeue() << '\n';
    std::cout << queue->dequeue() << '\n';
    std::cout << queue->dequeue() << '\n';
}
