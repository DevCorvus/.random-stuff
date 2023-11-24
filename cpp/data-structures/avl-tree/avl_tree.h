#include <memory>
#include <stdexcept>

struct Node {
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    unsigned int height;
    int balance_factor;
};

// Type of BBST (Balanced Binary Search Tree)
class AVLTree {
  public:
    bool is_empty() const { return size == 0; }
    unsigned int get_size() const { return size; }
    int get_root() const { return root->value; }

    void insert(const int value) {
        if (contains(value)) {
            throw std::logic_error("Duplicated value");
        }

        root = insert(root, value);
        size++;
    }

    bool contains(const int value) { return contains(root, value); }

    bool remove(const int value) {
        if (!contains(value)) {
            return false;
        }

        root = remove(root, value);
        size--;

        return true;
    }

  private:
    std::shared_ptr<Node> root;
    unsigned int size;

    std::shared_ptr<Node> create_node(const int value) {
        auto new_node = std::make_shared<Node>();

        new_node->value = value;
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->balance_factor = 0;
        new_node->height = 0;

        return new_node;
    }

    void update_node(std::shared_ptr<Node> &node) {
        auto left_height = node->left != nullptr ? node->left->height : -1;
        auto right_height = node->right != nullptr ? node->right->height : -1;

        node->height = 1 + std::max(left_height, right_height);

        node->balance_factor = right_height - left_height;
    }

    std::shared_ptr<Node> balance_left_left_case(std::shared_ptr<Node> &node) {
        return right_rotation(node);
    }

    std::shared_ptr<Node> balance_left_right_case(std::shared_ptr<Node> &node) {
        node->left = left_rotation(node->left);
        return balance_left_left_case(node);
    }

    std::shared_ptr<Node>
    balance_right_right_case(std::shared_ptr<Node> &node) {
        return left_rotation(node);
    }

    std::shared_ptr<Node> balance_right_left_case(std::shared_ptr<Node> &node) {
        node->right = right_rotation(node->right);
        return balance_right_right_case(node);
    }

    std::shared_ptr<Node> left_rotation(std::shared_ptr<Node> &node) {
        auto new_parent = node->right;
        node->right = new_parent->left;
        new_parent->left = node;

        update_node(node);
        update_node(new_parent);

        return new_parent;
    }

    std::shared_ptr<Node> right_rotation(std::shared_ptr<Node> &node) {
        auto new_parent = node->left;
        node->left = new_parent->right;
        new_parent->right = node;

        update_node(node);
        update_node(new_parent);

        return new_parent;
    }

    std::shared_ptr<Node> balance(std::shared_ptr<Node> &node) {
        if (node->balance_factor < -1) {
            if (node->left->balance_factor <= 0) {
                return balance_left_left_case(node);
            } else {
                return balance_left_right_case(node);
            }
        } else if (node->balance_factor > 1) {
            if (node->right->balance_factor >= 0) {
                return balance_right_right_case(node);
            } else {
                return balance_right_left_case(node);
            }
        }

        return node;
    }

    std::shared_ptr<Node> insert(std::shared_ptr<Node> &node, const int value) {
        if (node == nullptr) {
            return create_node(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }

        update_node(node);

        return balance(node);
    }

    bool contains(std::shared_ptr<Node> &node, const int value) const {
        if (node == nullptr) {
            return false;
        }

        if (node->value == value) {
            return true;
        }

        if (value < node->value) {
            return contains(node->left, value);
        } else {
            return contains(node->right, value);
        }
    }

    int find_min(std::shared_ptr<Node> &node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->value;
    }

    int find_max(std::shared_ptr<Node> &node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->value;
    }

    std::shared_ptr<Node> remove(std::shared_ptr<Node> &node, const int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                return node->right;
            } else if (node->right == nullptr) {
                return node->left;
            } else {
                if (node->left->height < node->right->height) {
                    int succesor_value = find_min(node->left);
                    node->value = succesor_value;
                    node->right = remove(node->right, succesor_value);
                } else {
                    int succesor_value = find_max(node->left);
                    node->value = succesor_value;
                    node->left = remove(node->left, succesor_value);
                }
            }
        }

        update_node(node);

        return balance(node);
    }
};
