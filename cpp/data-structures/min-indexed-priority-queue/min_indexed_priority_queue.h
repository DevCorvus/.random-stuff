#include <stdexcept>
#include <vector>

// This is a Min Indexed Priority Queue implemented using a Binary Heap

class MinIndexedPriorityQueue {
  public:
    MinIndexedPriorityQueue(unsigned int capacity) {
        this->pm = std::vector<int>();
        this->im = std::vector<int>();
        this->values = std::vector<int>();
        this->parent = std::vector<unsigned int>();
        this->child = std::vector<unsigned int>();
        this->capacity = capacity;
        this->size = 0;

        for (int i = 0; i < capacity; i++) {
            pm.push_back(-1);
            im.push_back(-1);
            values.push_back(-1);

            parent.push_back((i * 1) / 2);
            child.push_back((i * 2) + 1);
        }
    }

    unsigned int get_size() const { return size; }
    bool is_empty() const { return size == 0; }

    bool contains(unsigned int ki) {
        if (ki < 0 || ki >= capacity) {
            throw std::out_of_range("Key index out of bounds");
        }
        return pm[ki] != -1;
    }

    void insert(unsigned int ki, int value) {
        if (contains(ki)) {
            throw std::logic_error("Key index already exists");
        }

        pm[ki] = size;
        im[size] = ki;
        values[ki] = value;

        swim(size);
        size++;
    }

    int update(unsigned int ki, int value) {
        if (!contains(ki)) {
            throw std::logic_error("Key index does not exist");
        }

        int i = pm[ki];
        int old_value = values[ki];

        values[ki] = value;

        sink(i);
        swim(i);

        return old_value;
    }

    int peek_at(unsigned int ki) {
        if (!contains(ki)) {
            throw std::logic_error("Key index does not exist");
        }
        return values[ki];
    }

    int remove_at(unsigned int ki) {
        if (!contains(ki)) {
            throw std::logic_error("Key index does not exist");
        }

        int i = pm[ki];

        swap(i, --size);
        sink(i);
        swim(i);

        int value = values[ki];

        pm[ki] = -1;
        im[ki] = -1;
        values[ki] = -1;

        return value;
    }

    int peek_min_key_index() {
        if (is_empty()) {
            throw std::out_of_range("Priority queue empty");
        }
        return im[0];
    }

    int peek_min_value() {
        if (is_empty()) {
            throw std::out_of_range("Priority queue empty");
        }
        return values[peek_min_key_index()];
    }

    int poll_min_key_index() {
        if (is_empty()) {
            throw std::out_of_range("Priority queue empty");
        }
        auto ki = peek_min_key_index();
        remove_at(ki);
        return ki;
    }

    int poll_min_value() {
        if (is_empty()) {
            throw std::out_of_range("Priority queue empty");
        }
        return remove_at(peek_min_key_index());
    }

    void decrease(unsigned int ki, int value) {
        if (!contains(ki)) {
            throw std::logic_error("Key index does not exist");
        }

        if (value < values[ki]) {
            values[ki] = value;
            swim(pm[ki]);
        }
    }

    void increase(unsigned int ki, int value) {
        if (!contains(ki)) {
            throw std::logic_error("Key index does not exist");
        }

        if (value > values[ki]) {
            values[ki] = value;
            sink(pm[ki]);
        }
    }

  private:
    std::vector<int> pm;
    std::vector<int> im;
    std::vector<int> values;
    std::vector<unsigned int> parent;
    std::vector<unsigned int> child;
    unsigned int capacity;
    unsigned int size;

    void swap(int i, int j) {
        pm[im[j]] = i;
        pm[im[i]] = j;
        int tmp = im[i];
        im[i] = im[j];
        im[j] = tmp;
    }

    int min_child(int i) {
        int index = -1;

        auto from = child[i];
        auto to = std::min(size, from + 2);

        for (int j = from; j < to; j++) {
            if (values[im[j]] < values[im[i]]) {
                i = j;
                index = j;
            }
        }

        return index;
    }

    void sink(int i) {
        for (int j = min_child(i); j != -1;) {
            swap(i, j);
            i = j;
            j = min_child(i);
        }
    }

    void swim(int i) {
        while (values[im[i]] < values[im[parent[i]]]) {
            swap(i, parent[i]);
            i = parent[i];
        }
    }
};
