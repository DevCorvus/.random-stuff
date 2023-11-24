#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <stack>

struct TreeNode {
    int value;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
};

class BinarySearchTree {
  public:
    unsigned int get_size() const { return BinarySearchTree::size; }

    bool empty() const { return BinarySearchTree::size == 0; }

    unsigned int height() { return height(root); }

    void insert(int value) { insert(root, value); }

    bool remove(int target) { return remove(root, target); }

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

    void traverse_deep_first_recursive_preorder() {
        traverse_deep_first_recursive_preorder(root);
    }

    void traverse_deep_first_recursive_inorder() {
        traverse_deep_first_recursive_inorder(root);
    }

    void traverse_deep_first_recursive_postorder() {
        traverse_deep_first_recursive_postorder(root);
    }

    // Also called Level order traversal
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
    unsigned int size;

    std::shared_ptr<TreeNode> create_node(int value) {
        auto node = std::make_shared<TreeNode>();
        node->value = value;
        return node;
    }

    unsigned int height(std::shared_ptr<TreeNode> &node) {
        if (node == nullptr) {
            return 0;
        }
        return std::max(height(node->left), height(node->right)) + 1;
    }

    std::shared_ptr<TreeNode>
    get_smallest_child(std::shared_ptr<TreeNode> &node) {
        auto curr = node;

        while (curr->left != nullptr) {
            curr = curr->left;
        }

        return curr;
    }

    std::shared_ptr<TreeNode>
    get_biggest_child(std::shared_ptr<TreeNode> &node) {
        auto curr = node;

        while (curr->right != nullptr) {
            curr = curr->right;
        }

        return curr;
    }

    void insert(std::shared_ptr<TreeNode> &node, int value) {
        if (node == nullptr) {
            node = create_node(value);
            size++;
            return;
        }

        if (value < node->value) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }

    bool remove(std::shared_ptr<TreeNode> &node, int target) {
        if (node == nullptr) {
            return false;
        }

        if (node->value == target) {
            if (node->left == nullptr && node->right == nullptr) {
                node = nullptr;
            } else if (node->left != nullptr && node->right != nullptr) {
                // You can either use the right's smallest or left's biggest
                auto right_smallest = get_smallest_child(node->right);
                node->value = right_smallest->value;
                right_smallest = right_smallest->right;
            } else {
                if (node->left != nullptr) {
                    node = node->left;
                } else {
                    node = node->right;
                }
            }
            size--;
            return true;
        }

        if (target < node->value) {
            return remove(node->left, target);
        } else {
            return remove(node->right, target);
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

    void
    traverse_deep_first_recursive_preorder(std::shared_ptr<TreeNode> node) {
        if (node == nullptr) {
            return;
        }

        std::cout << node->value << '\n';

        traverse_deep_first_recursive_preorder(node->left);
        traverse_deep_first_recursive_preorder(node->right);
    }

    void traverse_deep_first_recursive_inorder(std::shared_ptr<TreeNode> node) {
        if (node == nullptr) {
            return;
        }

        traverse_deep_first_recursive_inorder(node->left);
        std::cout << node->value << '\n';
        traverse_deep_first_recursive_inorder(node->right);
    }

    void
    traverse_deep_first_recursive_postorder(std::shared_ptr<TreeNode> node) {
        if (node == nullptr) {
            return;
        }

        traverse_deep_first_recursive_postorder(node->left);
        traverse_deep_first_recursive_postorder(node->right);
        std::cout << node->value << '\n';
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
