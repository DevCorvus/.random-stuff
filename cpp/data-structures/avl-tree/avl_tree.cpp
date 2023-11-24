#include "avl_tree.h"
#include <iostream>

int main(void) {
    auto avl = std::make_unique<AVLTree>();

    std::cout << "Empty: " << avl->is_empty() << '\n';
    std::cout << "Contains 4: " << avl->contains(4) << '\n';
    std::cout << "Remove 4: " << avl->remove(4) << '\n';

    avl->insert(4);

    std::cout << "Empty: " << avl->is_empty() << '\n';
    std::cout << "Contains 4: " << avl->contains(4) << '\n';
    std::cout << "Remove 4: " << avl->remove(4) << '\n';
    std::cout << "Contains 4: " << avl->contains(4) << '\n';

    avl->insert(6);
    avl->insert(9);
    avl->insert(4);
    avl->insert(2);
    avl->insert(0);

    std::cout << "Size: " << avl->get_size() << '\n';

    std::cout << "Root: " << avl->get_root() << '\n';
    std::cout << "Remove 6: " << avl->remove(6) << '\n';
    std::cout << "Root: " << avl->get_root() << '\n';
    std::cout << "Remove 4: " << avl->remove(4) << '\n';
    std::cout << "Root: " << avl->get_root() << '\n';
}
