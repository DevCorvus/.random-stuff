#include "doubly_linked_list.h"
#include <iostream>

int main(void) {
    auto doubly_linked_list =
        std::make_unique<DoublyLinkedList<unsigned int>>();

    doubly_linked_list->insertAtHead(4);
    doubly_linked_list->insertAtTail(8);
    doubly_linked_list->insertAtHead(1);
    doubly_linked_list->insertAt(1, 7);

    std::cout << "Remove at: " << doubly_linked_list->removeAt(2) << '\n';

    std::cout << "Size: " << doubly_linked_list->getSize() << '\n';
    std::cout << "First: " << doubly_linked_list->peekFirst() << '\n';
    std::cout << "Last: " << doubly_linked_list->peekLast() << '\n';
    std::cout << "At Index: " << doubly_linked_list->peekAt(1) << '\n';
}
