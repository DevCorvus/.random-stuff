#include <stdexcept>
#include <vector>

// This is a Min Priority Queue implemented using a Binary Heap
// The Heap is using a vector representation which is highly efficient (?)

class MinPriorityQueue {
  public:
    MinPriorityQueue() { this->heap = std::vector<int>(); }

    unsigned int get_size() const { return heap.size(); }

    bool empty() const { return get_size() == 0; }

    void insert(int value) {
        heap.push_back(value);
        swim(get_size() - 1);
    }

    int remove() {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }

        auto removed_value = heap[0];

        swap(0, get_size() - 1);
        heap.pop_back();

        auto root_before_sink = heap[0];

        sink(0);

        auto root_after_sink = heap[0];

        if (root_after_sink == root_before_sink) {
            swim(0);
        }

        return removed_value;
    }

    int peek() const { return heap[0]; }

  private:
    std::vector<int> heap;

    void swim(unsigned int i) {
        auto parent = (i - 1) / 2;

        // This could be recursive
        while (i > 0 && is_less(i, parent)) {
            swap(i, parent);

            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void sink(unsigned int i) {
        // This can also be recursive
        while (true) {
            auto left = 2 * i + 1;
            auto right = 2 * i + 2;

            auto size = get_size();

            if (left >= size || right >= size) {
                break;
            }

            unsigned int smallest;

            if (is_less(left, right)) {
                smallest = left;
            } else {
                smallest = right;
            }

            if (is_less(smallest, i)) {
                swap(i, smallest);
                i = smallest;
            } else {
                break;
            }
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
};
