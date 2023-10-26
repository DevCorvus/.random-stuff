#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINED -1
#define SUCCESS 0

#define VECTOR_INIT(vec)                                                       \
    vector vec;                                                                \
    vector_init(&vec);

typedef struct {
    void **data;
    int total;
    int capacity;
} VectorList;

typedef struct Vector vector;

struct Vector {
    VectorList vectorList;

    int (*vectorTotal)(vector *);
    int (*vectorResize)(vector *, int);
    int (*vectorPush)(vector *, void *);
    int (*vectorSet)(vector *, int, void *);
    void *(*vectorGet)(vector *, int);
    int (*vectorDelete)(vector *, int);
    int (*vectorFree)(vector *);
};

int vectorTotal(vector *v) {
    int total = UNDEFINED;

    if (v) {
        total = v->vectorList.total;
    }

    return total;
}

int vectorResize(vector *v, int capacity) {
    int status = UNDEFINED;

    if (v) {
        void **data = realloc(v->vectorList.data, sizeof(void *) * capacity);
        if (data) {
            v->vectorList.data = data;
            v->vectorList.capacity = capacity;
            status = SUCCESS;
        }
    }

    return status;
}

int vectorPush(vector *v, void *item) {
    int status = UNDEFINED;

    if (v) {
        if (v->vectorList.total == v->vectorList.capacity) {
            status = vectorResize(v, v->vectorList.capacity * 2);
            if (status == SUCCESS) {
                v->vectorList.data[v->vectorList.total++] = item;
            }
        } else {
            v->vectorList.data[v->vectorList.total++] = item;
            status = SUCCESS;
        }
    }

    return status;
}

int vectorSet(vector *v, int index, void *item) {
    int status = UNDEFINED;

    if (v) {
        if (index >= 0 && index < v->vectorList.total) {
            v->vectorList.data[index] = item;
            status = SUCCESS;
        }
    }

    return status;
}

void *vectorGet(vector *v, int index) {
    void *item = NULL;

    if (v) {
        if (index >= 0 && index < v->vectorList.total) {
            item = v->vectorList.data[index];
        }
    }

    return item;
}

int vectorDelete(vector *v, int index) {
    int status = UNDEFINED;

    if (v) {
        if (index < 0 || index >= v->vectorList.total)
            return status;

        v->vectorList.data[index] = NULL;

        for (int i = 0; i < v->vectorList.total; i++) {
            v->vectorList.data[i] = v->vectorList.data[i + 1];
            v->vectorList.data[i + 1] = NULL;
        }

        v->vectorList.total--;

        if (v->vectorList.total > 0 &&
            v->vectorList.total == v->vectorList.capacity / 4) {
            vectorResize(v, v->vectorList.capacity / 2);
        }

        status = SUCCESS;
    }

    return status;
}

int vectorFree(vector *v) {
    int status = UNDEFINED;

    if (v) {
        free(v->vectorList.data);
        v->vectorList.data = NULL;
        status = SUCCESS;
    }

    return status;
}

void vector_init(vector *v) {
    v->vectorTotal = vectorTotal;
    v->vectorResize = vectorResize;
    v->vectorPush = vectorPush;
    v->vectorSet = vectorSet;
    v->vectorGet = vectorGet;
    v->vectorDelete = vectorDelete;
    v->vectorFree = vectorFree;

    v->vectorList.capacity = VECTOR_INIT_CAPACITY;
    v->vectorList.total = 0;
    v->vectorList.data = malloc(sizeof(void *) * v->vectorList.capacity);
};

int main(void) {
    printf("Hello World \n");

    VECTOR_INIT(v);

    int iterations = 10;

    for (int i = 0; i < iterations; i++) {
        v.vectorPush(&v, "Hello World");
    }

    v.vectorSet(&v, 4, "Bye World");

    for (int i = 0; i < iterations; i++) {
        printf("%s\n", (char *)v.vectorList.data[i]);
    }

    printf("%s\n", (char *)v.vectorGet(&v, 10));

    return 0;
}
