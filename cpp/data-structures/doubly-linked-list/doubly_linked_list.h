#include <memory>
#include <stdexcept>

template <typename T> struct Node {
    T data;
    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;
};

template <typename T> class DoublyLinkedList {
  public:
    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    unsigned int getSize() { return DoublyLinkedList::size; }

    bool isEmpty() { return DoublyLinkedList::size == 0; }

    void insertAtHead(T data) {
        auto node = std::make_shared<Node<T>>();
        node->data = data;

        if (isEmpty()) {
            this->head = node;
            this->tail = node;
        } else {
            node->next = this->head;
            this->head->prev = node;
            this->head = node;
        }

        this->size++;
    }

    void insertAtTail(T data) {
        auto node = std::make_shared<Node<T>>();
        node->data = data;

        if (isEmpty()) {
            this->head = node;
            this->tail = node;
        } else {
            node->prev = this->tail;
            this->tail->next = node;
            this->tail = node;
        }

        this->size++;
    }

    void insertAt(unsigned int index, T data) {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        } else if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            return insertAtHead(data);
        } else if (index == (this->size - 1)) {
            return insertAtTail(data);
        } else {
            auto node = std::make_shared<Node<T>>();
            node->data = data;

            auto curr = this->head;

            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }

            node->prev = curr->prev;
            node->next = curr;

            curr->prev->next = node;
            curr->prev = node;

            size++;
        }
    }

    T peekFirst() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return this->head->data;
    }

    T peekLast() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return this->tail->data;
    }

    T peekAt(unsigned int index) {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        } else if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range");
        }

        auto curr = this->head;

        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }

        return curr->data;
    }

    T removeFirst() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }

        auto prev_head = this->head;
        this->head = this->head->next;

        auto data = prev_head->data;
        prev_head = nullptr;

        size--;

        return data;
    }

    T removeLast() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }

        auto prev_tail = this->tail;
        this->tail = this->tail->prev;

        auto data = prev_tail->data;
        prev_tail = nullptr;

        size--;

        return data;
    }

    T removeAt(unsigned int index) {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        } else if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            return removeFirst();
        } else if (index == (this->size - 1)) {
            return removeLast();
        } else {
            auto curr = this->head;

            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }

            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            auto data = curr->data;
            curr = nullptr;

            size--;

            return data;
        }
    }

  private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    unsigned int size;
};
