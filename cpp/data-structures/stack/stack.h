#include <memory>
#include <stdexcept>

template <typename T> struct Node {
    T data;
    std::unique_ptr<Node> next;
};

template <typename T> class Stack {
  public:
    Stack() {
        this->top = nullptr;
        this->size = 0;
    }

    unsigned int get_size() { return Stack::size; }

    bool empty() { return Stack::size == 0; }

    void push(T data) {
        auto node = std::make_unique<Node<T>>();
        node->data = data;

        if (this->top == nullptr) {
            this->top = std::move(node);
        } else {
            node->next = std::move(this->top);
            this->top = std::move(node);
        }

        this->size++;
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }

        auto data = this->top->data;

        this->top = std::move(this->top->next);

        this->size--;

        return data;
    }

  private:
    std::unique_ptr<Node<T>> top;
    unsigned int size;
};
