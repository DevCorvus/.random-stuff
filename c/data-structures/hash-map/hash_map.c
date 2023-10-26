#include "hash_map.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Iterator
// TODO: More performant data structure for buckets (currently LinkedLists)
// TODO: Resizing is not properly implemented and capacity can go under minimum
// TODO: Better hashing algorithm

uint64_t hash_key(char *key) {
    uint64_t hash = FNV_OFFSET;
    for (const char *p = key; *p; p++) {
        hash ^= *p;
        hash *= FNV_PRIME;
    }
    return hash;
}

size_t hm_hash_key(char *key, int capacity) {
    uint64_t hash = hash_key(key);
    return hash & (capacity - 1);
}

bool set_node(node *node, char *key, char *value) {
    bool status = false;

    char *newKey = malloc(sizeof(char) * (strlen(key) + 1));
    char *newValue = malloc(sizeof(char) * strlen(value) + 1);

    if (newKey && newValue) {
        strcpy(newKey, key);
        strcpy(newValue, value);

        node->key = newKey;
        node->value = newValue;
        node->next = NULL;

        status = true;
    } else {
        free(newKey);
        free(newValue);
    }

    return status;
}

bool hm_set_node(node **arr, int capacity, char *key, char *value) {
    bool status = false;

    node *newNode = malloc(sizeof(node));

    if (newNode) {
        status = set_node(newNode, key, value);

        if (status) {
            size_t index = hm_hash_key(key, capacity);

            if (arr[index] == NULL) {
                arr[index] = newNode;
            } else {
                newNode->next = arr[index];
                arr[index] = newNode;
            }
        }
    }

    return status;
}

bool hm_update_node(hash_map *mp, char *key, char *value) {
    bool status = false;

    size_t index = hm_hash_key(key, mp->capacity);

    node *bucketHead = mp->arr[index];
    while (bucketHead != NULL) {
        if (strcmp(bucketHead->key, key) == 0) {
            bucketHead->value = value;
            status = true;
            break;
        }
        bucketHead = bucketHead->next;
    }

    return status;
}

bool hm_resize(hash_map *mp, int capacity) {
    bool status = false;

    node **arr = malloc(sizeof(node) * capacity);
    if (arr) {
        for (int i = 0; i < mp->capacity; i++) {
            node *currNode = mp->arr[i];
            while (currNode != NULL) {
                hm_set_node(arr, capacity, currNode->key, currNode->value);
                free(currNode->key);
                free(currNode->value);
                free(currNode);
                currNode = currNode->next;
            }
        }
        free(mp->arr);
        mp->arr = arr;
        mp->capacity = capacity;
        status = true;
    }

    return status;
}

bool hm_put(hash_map *mp, char *key, char *value) {
    bool status = false;
    if (mp && key && value) {
        char *prevValue = mp->hm_get(mp, key);

        if (prevValue) {
            status = hm_update_node(mp, key, value);
        } else {
            if (mp->total == mp->capacity) {
                status = hm_resize(mp, mp->capacity * 2);
                if (status) {
                    status = hm_set_node(mp->arr, mp->capacity, key, value);
                }
            } else {
                status = hm_set_node(mp->arr, mp->capacity, key, value);
            }

            if (status) {
                mp->total++;
            }
        }
    }
    return status;
}

char *hm_get(hash_map *mp, char *key) {
    if (mp) {
        size_t index = hm_hash_key(key, mp->capacity);

        node *bucketHead = mp->arr[index];
        while (bucketHead != NULL) {
            if (strcmp(bucketHead->key, key) == 0) {
                return bucketHead->value;
            }
            bucketHead = bucketHead->next;
        }
    }
    return NULL;
}

bool hm_delete(hash_map *mp, char *key) {
    bool status = false;
    if (mp) {
        size_t index = hm_hash_key(key, mp->capacity);

        node *prevNode = NULL;
        node *currNode = mp->arr[index];

        while (currNode != NULL) {
            if (strcmp(currNode->key, key) == 0) {
                // Head node
                if (currNode == mp->arr[index]) {
                    mp->arr[index] = currNode->next;
                }
                // Last node or middle node
                else {
                    prevNode->next = currNode->next;
                }

                free(currNode->key);
                free(currNode->value);
                free(currNode);
                mp->total--;
                status = true;

                if (mp->total > 0 && mp->total == (mp->capacity / 4)) {
                    status = hm_resize(mp, mp->capacity / 2);
                }

                break;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }
    return status;
}

bool hm_free(hash_map *mp) {
    bool status = false;
    if (mp) {
        for (int i = 0; i < mp->capacity; i++) {
            node *currNode = mp->arr[i];
            while (currNode != NULL) {
                free(currNode->key);
                free(currNode->value);
                free(currNode);
                currNode = currNode->next;
            }
        }
        free(mp->arr);
        mp->arr = NULL;
        status = true;
    }
    return status;
}

void init_hash_map(hash_map *mp) {
    mp->capacity = HASH_MAP_INIT_CAPACITY;
    mp->total = 0;
    mp->arr = malloc(sizeof(node *) * mp->capacity);

    mp->hm_put = hm_put;
    mp->hm_get = hm_get;
    mp->hm_delete = hm_delete;
    mp->hm_free = hm_free;
}
