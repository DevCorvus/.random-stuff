#include "hash_node.h"
#include "key_hash.h"

template <typename K, typename V, typename F = KeyHash<K>> class HashMap {
  public:
    HashMap() { table = new HashNode<K, V> *[TABLE_SIZE](); }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode<K, V> *entry = table[i];

            while (entry != NULL) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }

            table[i] = NULL;
        }

        delete[] table;
    }

    V get(const K &key) const {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->getKey() == key) {
                return entry->getValue();
            }
            entry = entry->getNext();
        }

        return NULL;
    }

    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry != NULL) {
            entry->setValue(value);
        } else {
            entry = new HashNode<K, V>(key, value);
            if (prev == NULL) {
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            return;
        }

        if (prev == NULL) {
            table[hashValue] = entry->getNext();
        } else {
            prev->setNext(entry->getNext());
        }
        delete entry;
    }

  private:
    HashNode<K, V> **table;
    F hashFunc;
};
