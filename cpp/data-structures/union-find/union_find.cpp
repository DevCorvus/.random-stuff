#include "union_find.h"
#include <iostream>
#include <memory>

int main(void) {
    auto uf = std::make_unique<UnionFind>(10);

    uf->unify(0, 3);
    uf->unify(4, 3);

    std::cout << "Size: " << uf->get_size() << '\n';
    std::cout << "Root of 4: " << uf->find(4) << '\n';
    std::cout << "Set size of 4: " << uf->get_set_size(4) << '\n';
    std::cout << "Num of sets: " << uf->get_num_sets() << '\n';
}
