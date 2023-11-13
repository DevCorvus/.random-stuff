#include "binary_search_tree.h"

int main(void) {
    std::unique_ptr<BinarySearchTree> bst =
        std::make_unique<BinarySearchTree>();

    bst->insert(4);
    bst->insert(3);
    bst->insert(2);
    bst->insert(6);
    bst->insert(9);

    std::cout << "Size: " << bst->get_size() << '\n';
    std::cout << "Height: " << bst->height() << '\n';

    std::cout << "Remove 9: " << bst->remove(9) << '\n';

    std::cout << "Size: " << bst->get_size() << '\n';
    std::cout << "Height: " << bst->height() << '\n';

    std::cout << "Binary search 6: " << bst->binary_search(6) << '\n';

    std::cout << "Traverse deep first:" << '\n';
    bst->traverse_deep_first();

    std::cout << "Traverse deep first recursive (preorder):" << '\n';
    bst->traverse_deep_first_recursive_preorder();

    std::cout << "Traverse deep first recursive (inorder):" << '\n';
    bst->traverse_deep_first_recursive_inorder();

    std::cout << "Traverse deep first recursive (postorder):" << '\n';
    bst->traverse_deep_first_recursive_postorder();

    std::cout << "Traverse breadth first:" << '\n';
    bst->traverse_breadth_first();

    std::cout << "Search deep first 6: " << bst->search_deep_first(6) << '\n';

    std::cout << "Search breadth first 6: " << bst->search_breadth_first(6)
              << '\n';

    std::cout << "Includes 6: " << bst->includes(6) << '\n';

    std::cout << "Sum: " << bst->sum() << '\n';

    std::cout << "Sum (recursive): " << bst->sum_recursive() << '\n';

    std::cout << "Min: " << bst->min() << '\n';

    std::cout << "Min (recursive): " << bst->min_recursive() << '\n';

    std::cout << "Binary search MIN: " << bst->binary_search_min() << '\n';

    std::cout << "Binary search MAX: " << bst->binary_search_max() << '\n';

    std::cout << "Max path sum: " << bst->max_path_sum() << '\n';
}
