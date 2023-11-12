#include "min_priority_queue.h"
#include <iostream>
#include <memory>

int main(void) {
    auto pq = std::make_unique<MinPriorityQueue>();
    pq->push(4);
    pq->push(3);
    pq->push(7);
    pq->push(1);
    pq->push(9);
    pq->push(5);
    pq->push(8);
    pq->push(2);
    pq->push(4);

    std::cout << "Contains 5: " << pq->contains(5) << '\n';
    std::cout << "Contains 6: " << pq->contains(6) << '\n';

    std::cout << "Remove 3: " << pq->remove(3) << '\n';

    auto size = pq->get_size();
    std::cout << "Size: " << size << '\n';

    for (int i = 0; i < size; i++) {
        std::cout << "Removed: " << pq->pop() << '\n';
    }

    pq->pop();
}
