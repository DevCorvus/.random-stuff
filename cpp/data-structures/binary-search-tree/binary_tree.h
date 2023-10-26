#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <stack>

// If I weren't using data structures that require ownership like stacks and
// queues then you should use unique_ptr

struct TreeNode {
    int value;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
};

class BinarySearchTree {
  public:
    void insert(int value) { insert(root, value); }

    bool binary_search(int target) { return binary_search(root, target); }

    void traverse_deep_first() {
        if (root == nullptr) {
            return;
        }

        std::stack<std::shared_ptr<TreeNode>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto curr = stack.top();
            std::cout << curr->value << '\n';
            stack.pop();

            if (curr->right != nullptr) {
                stack.push(curr->right);
            }
            if (curr->left != nullptr) {
                stack.push(curr->left);
            }
        }
    }

    void traverse_deep_first_recursive() {
        traverse_deep_first_recursive(root);
    }

    void traverse_breadth_first() {
        if (root == nullptr) {
            return;
        }

        std::queue<std::shared_ptr<TreeNode>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto curr = stack.front();
            std::cout << curr->value << '\n';
            stack.pop();

            if (curr->left != nullptr) {
                stack.push(curr->left);
            }
            if (curr->right != nullptr) {
                stack.push(curr->right);
            }
        }
    }

    bool search_deep_first(int target) {
        if (root == nullptr) {
            return false;
        }

        std::stack<std::shared_ptr<TreeNode>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto curr = stack.top();
            if (curr->value == target) {
                return true;
            }
            stack.pop();

            if (curr->left != nullptr) {
                stack.push(curr->left);
            }
            if (curr->right != nullptr) {
                stack.push(curr->right);
            }
        }

        return false;
    }

    bool search_breadth_first(int target) {
        if (root == nullptr) {
            return false;
        }

        std::queue<std::shared_ptr<TreeNode>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto curr = stack.front();
            if (curr->value == target) {
                return true;
            }
            stack.pop();

            if (curr->left != nullptr) {
                stack.push(curr->left);
            }
            if (curr->right != nullptr) {
                stack.push(curr->right);
            }
        }

        return false;
    }

    bool includes(int target) { return includes(root, target); }

    int sum() {
        int total = 0;

        if (root == nullptr) {
            return total;
        }

        std::stack<std::shared_ptr<TreeNode>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto curr = stack.top();
            total += curr->value;
            stack.pop();

            if (curr->right != nullptr) {
                stack.push(curr->right);
            }
            if (curr->left != nullptr) {
                stack.push(curr->left);
            }
        }

        return total;
    }

    int sum_recursive() { return sum_recursive(root); }

    int min() {
        int curr_min = std::numeric_limits<int>::max();

        if (root == nullptr) {
            return curr_min;
        }

        std::stack<std::shared_ptr<TreeNode>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto curr = stack.top();
            if (curr->value < curr_min) {
                curr_min = curr->value;
            }
            stack.pop();

            if (curr->right != nullptr) {
                stack.push(curr->right);
            }
            if (curr->left != nullptr) {
                stack.push(curr->left);
            }
        }

        return curr_min;
    }

    int min_recursive() { return min_recursive(root); }

    int binary_search_min() {
        if (root == nullptr) {
            return std::numeric_limits<int>::max();
        }

        auto curr = root;

        while (curr->left != nullptr) {
            curr = curr->left;
        }

        return curr->value;
    }

    int binary_search_max() {
        if (root == nullptr) {
            return std::numeric_limits<int>::min();
        }

        auto curr = root;

        while (curr->right != nullptr) {
            curr = curr->right;
        }

        return curr->value;
    }

    int max_path_sum() { return max_path_sum(root); }

  private:
    std::shared_ptr<TreeNode> root;

    std::shared_ptr<TreeNode> createNode(int value) {
        auto node = std::make_shared<TreeNode>();
        node->value = value;
        return node;
    }

    void insert(std::shared_ptr<TreeNode> &node, int value) {
        if (node == nullptr) {
            node = createNode(value);
            return;
        }

        if (value < node->value) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }

    bool binary_search(std::shared_ptr<TreeNode> &node, int target) {
        if (node == nullptr) {
            return false;
        }

        if (node->value == target) {
            return true;
        }

        if (target < node->value) {
            return binary_search(node->left, target);
        } else {
            return binary_search(node->right, target);
        }
    }

    void traverse_deep_first_recursive(std::shared_ptr<TreeNode> node) {
        if (node == nullptr) {
            return;
        }

        std::cout << node->value << '\n';

        traverse_deep_first_recursive(node->left);
        traverse_deep_first_recursive(node->right);
    }

    bool includes(std::shared_ptr<TreeNode> node, int target) {
        if (node == nullptr) {
            return false;
        }

        if (node->value == target) {
            return true;
        }

        return includes(node->left, target) || includes(node->right, target);
    }

    int sum_recursive(std::shared_ptr<TreeNode> node) {
        if (node == nullptr) {
            return 0;
        }

        return node->value +
               (sum_recursive(node->left) + sum_recursive(node->right));
    }

    int min_recursive(std::shared_ptr<TreeNode> node) {
        if (node == nullptr) {
            return std::numeric_limits<int>::max();
        }

        return std::min(node->value, std::min(min_recursive(node->left),
                                              min_recursive(node->right)));
    }

    int max_path_sum(std::shared_ptr<TreeNode> node) {
        if (node == nullptr) {
            return 0;
        }

        return node->value +
               std::max(max_path_sum(node->left), max_path_sum(node->right));
    }
};
