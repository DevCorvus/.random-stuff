#include "min_indexed_priority_queue.h"
#include <iostream>
#include <memory>

int main(void) {
    auto ipq = std::make_unique<MinIndexedPriorityQueue>(32);

    std::cout << "Size: " << ipq->get_size() << '\n';
    std::cout << "Is Empty: " << ipq->is_empty() << '\n';

    std::cout << "Contains 0: " << ipq->contains(0) << '\n';

    ipq->insert(0, 9);
    ipq->insert(1, 6);
    ipq->insert(2, 3);

    std::cout << "Size: " << ipq->get_size() << '\n';
    std::cout << "Is Empty: " << ipq->is_empty() << '\n';

    std::cout << "Contains 0: " << ipq->contains(0) << '\n';
    std::cout << "Peek at 0: " << ipq->peek_at(0) << '\n';

    std::cout << "Peek min key index: " << ipq->peek_min_key_index() << '\n';
    std::cout << "Peek min value: " << ipq->peek_min_value() << '\n';

    std::cout << "Updated value at key index 2: " << ipq->update(2, 7) << '\n';
    std::cout << "Peek min value: " << ipq->peek_min_value() << '\n';

    ipq->insert(3, 2);
    ipq->insert(4, 4);

    std::cout << "Poll min key index: " << ipq->poll_min_key_index() << '\n';
    std::cout << "Poll min value: " << ipq->poll_min_value() << '\n';
}
