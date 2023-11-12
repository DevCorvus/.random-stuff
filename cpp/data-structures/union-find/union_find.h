#include <vector>

// Also called Disjoint Set
class UnionFind {
  public:
    UnionFind(int n) {
        this->parents = std::vector<int>(n);
        this->sizes = std::vector<int>(n);

        this->size = n;
        this->num_sets = n;

        for (int i = 0; i < n; i++) {
            this->parents[i] = i;
            this->sizes[i] = 1;
        }
    }

    unsigned int get_size() const { return UnionFind::size; }

    unsigned int get_num_sets() const { return UnionFind::num_sets; }

    unsigned int get_set_size(int x) { return sizes[find(x)]; }

    int find(int i) {
        if (parents[i] == i) {
            return i;
        } else {
            int next_parent = find(parents[i]);
            parents[i] = next_parent; // Path compression
            return next_parent;
        }
    }

    void unify(int i, int j) {
        int i_root = find(i);
        int j_root = find(j);

        if (i_root == j_root) {
            return;
        }

        if (sizes[i_root] < sizes[j_root]) {
            sizes[j_root] += sizes[i_root];
            parents[i_root] = j_root;
            sizes[i_root] = 0;
        } else {
            sizes[i_root] += sizes[j_root];
            parents[j_root] = i_root;
            sizes[j_root] = 0;
        }

        num_sets--;
    }

  private:
    std::vector<int> parents;
    std::vector<int> sizes;
    unsigned int size;
    unsigned int num_sets;
};
