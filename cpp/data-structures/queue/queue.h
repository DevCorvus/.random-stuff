#include <memory>
#include <stdexcept>

template <typename T> struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
};

template <typename T> class Queue {
  public:
    Queue() {
        this->front = nullptr;
        this->back = nullptr;
        this->size = 0;
    }

    unsigned int get_size() const { return Queue::size; }

    bool empty() const { return Queue::size == 0; }

    void enqueue(T data) {
        auto node = std::make_shared<Node<T>>();
        node->data = data;

        if (this->empty()) {
            this->front = node;
            this->back = node;
        } else {
            this->back->next = node;
            this->back = node;
        }

        this->size++;
    }

    T dequeue() {
        if (this->empty()) {
            throw std::out_of_range("Queue is empty");
        }

        auto data = this->front->data;
        this->front = this->front->next;

        if (this->front == nullptr) {
            this->back = nullptr;
        }

        this->size--;

        return data;
    }

    T peek() const { return this->front->data; }

  private:
    std::shared_ptr<Node<T>> front;
    std::shared_ptr<Node<T>> back;
    unsigned int size;
};
