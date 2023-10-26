#define TABLE_SIZE 100

template <typename K> struct KeyHash {
    unsigned long operator()(const K &key) const {
        return static_cast<unsigned long>(key) % TABLE_SIZE;
    }
};
