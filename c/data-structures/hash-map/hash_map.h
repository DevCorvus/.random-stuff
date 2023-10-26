#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdbool.h>

#define HASH_MAP_INIT_CAPACITY 16

#define HASH_MAP_INIT(mp)                                                      \
    hash_map mp;                                                               \
    init_hash_map(&mp);

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct Node node;

struct Node {
    char *key;
    void *value;
    node *next;
};

typedef struct HashMap hash_map;

struct HashMap {
    int capacity, total;
    node **arr;

    bool (*hm_put)(hash_map *, char *, char *);
    char *(*hm_get)(hash_map *, char *);
    bool (*hm_delete)(hash_map *, char *);
    bool (*hm_free)(hash_map *);
};

void init_hash_map(hash_map *);

#endif
