#include "min_priority_queue.h"
#include <iostream>
#include <memory>

int main(void) {
    auto pq = std::make_unique<MinPriorityQueue>();
    pq->insert(4);
    pq->insert(3);
    pq->insert(7);
    pq->insert(1);
    pq->insert(9);
    pq->insert(5);
    pq->insert(8);
    pq->insert(2);
    pq->insert(4);

    auto size = pq->get_size();
    std::cout << "Size: " << size << '\n';

    for (int i = 0; i < size; i++) {
        std::cout << "Removed: " << pq->remove() << '\n';
    }

    pq->remove();
}
