#include <stdexcept>
#include <vector>

// This is a Min Priority Queue implemented using a Binary Heap
// The Heap is using a vector representation which is highly efficient (?)

class MinPriorityQueue {
  public:
    MinPriorityQueue() { this->heap = std::vector<int>(); }

    unsigned int get_size() const { return heap.size(); }

    bool empty() const { return get_size() == 0; }

    void push(int value) {
        heap.push_back(value);
        shift_up(get_size() - 1);
    }

    int pop() { return remove_at(0); }

    int peek() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    bool contains(int value) const {
        auto size = get_size();

        for (int i = 0; i < size; i++) {
            if (heap[i] == value) {
                return true;
            }
        }

        return false;
    }

    bool remove(int value) {
        auto size = get_size();

        for (int i = 0; i < size; i++) {
            if (heap[i] == value) {
                remove_at(i);
                return true;
            }
        }

        return false;
    }

  private:
    std::vector<int> heap;

    void shift_up(unsigned int i) {
        auto parent = (i - 1) / 2;

        if (i > 0 && is_less(i, parent)) {
            swap(i, parent);
            shift_up(parent);
        }
    }

    void shift_down(unsigned int i) {
        auto left = 2 * i + 1;
        auto right = 2 * i + 2;
        unsigned int smallest = i;

        auto size = get_size();

        if (left < size && is_less(left, smallest)) {
            smallest = left;
        }

        if (right < size && is_less(right, smallest)) {
            smallest = right;
        }

        if (smallest != i) {
            swap(i, smallest);
            shift_down(smallest);
        }
    }

    bool is_less(unsigned int i, unsigned int j) const {
        return heap[i] <= heap[j];
    }

    void swap(unsigned int i, unsigned int j) {
        auto elem_i = heap[i];
        auto elem_j = heap[j];

        heap[i] = elem_j;
        heap[j] = elem_i;
    }

    int remove_at(unsigned int i) {
        auto size = get_size();

        if (empty() || i >= size) {
            throw std::out_of_range("Heap is empty");
        }

        auto removed_value = heap[i];

        swap(i, size - 1);
        heap.pop_back();

        auto root_before = heap[0];

        shift_down(i);

        auto root_after = heap[0];

        if (root_after == root_before) {
            shift_up(i);
        }

        return removed_value;
    }
};
