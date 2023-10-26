#include "binary_tree.h"
#include <iostream>

int main(void) {
    std::unique_ptr<BinarySearchTree> binaryTree = std::make_unique<BinarySearchTree>();

    binaryTree->insert(4);
    binaryTree->insert(3);
    binaryTree->insert(2);
    binaryTree->insert(6);

    std::cout << "Binary search 6: " << binaryTree->binary_search(6) << '\n';

    std::cout << "Traverse deep first:" << '\n';
    binaryTree->traverse_deep_first();

    std::cout << "Traverse deep first (recursive):" << '\n';
    binaryTree->traverse_deep_first_recursive();

    std::cout << "Traverse breadth first:" << '\n';
    binaryTree->traverse_breadth_first();

    std::cout << "Search deep first 6: " << binaryTree->search_deep_first(6)
              << '\n';

    std::cout << "Search breadth first 6: "
              << binaryTree->search_breadth_first(6) << '\n';

    std::cout << "Includes 6: " << binaryTree->includes(6) << '\n';

    std::cout << "Sum: " << binaryTree->sum() << '\n';

    std::cout << "Sum (recursive): " << binaryTree->sum_recursive() << '\n';

    std::cout << "Min: " << binaryTree->min() << '\n';

    std::cout << "Min (recursive): " << binaryTree->min_recursive() << '\n';

    std::cout << "Binary search MIN: " << binaryTree->binary_search_min()
              << '\n';

    std::cout << "Binary search MAX: " << binaryTree->binary_search_max()
              << '\n';

    std::cout << "Max path sum: " << binaryTree->max_path_sum() << '\n';
}
