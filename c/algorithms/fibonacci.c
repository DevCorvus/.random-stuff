#include "../data-structures/hash-map/hash_map.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long fib(int n) {
    long a = 0, b = 1, total;
    for (int i = 2; i <= n; i++) {
        total = a + b;

        a = b;
        b = total;
    }
    return total;
}

long fib_sequence(int n, bool display) {
    long sequence[n];

    sequence[0] = 0;
    sequence[1] = 1;

    for (int i = 2; i <= n; i++) {
        sequence[i] = sequence[i - 1] + sequence[i - 2];
    }

    if (display) {
        printf("[");
        for (int i = 0; i <= n; i++) {
            printf("%lu", sequence[i]);
            if (i != n) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    return sequence[n];
}

long fib_recursive(int n) {
    if (n <= 1) {
        return n;
    }

    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

char *convert_usize_to_string(size_t n) {
    int len = snprintf(NULL, 0, "%lu", n);
    char *str = malloc(sizeof(char) * (len + 1));
    sprintf(str, "%lu", n);

    return str;
}

long fib_recursive_optimized(int n, hash_map *mp) {
    if (n <= 1)
        return n;

    long result;

    char *key = convert_usize_to_string(n);

    char *value = mp->hm_get(mp, key);
    if (value) {
        result = strtol(value, NULL, 10);
    } else {
        result = fib_recursive_optimized(n - 1, mp) +
                 fib_recursive_optimized(n - 2, mp);

        char *result_str = convert_usize_to_string(result);

        mp->hm_put(mp, key, result_str);
        free(result_str);
    }

    free(key);
    return result;
}

int main(void) {
    printf("Fibonacci algorithms:\n\n");

    int n = 40;

    clock_t t;
    double elapsed;

    t = clock();
    printf("Iteration (Total sum): %lu\n", fib(n));
    t = clock() - t;
    elapsed = (double)t / CLOCKS_PER_SEC;
    printf("took %f seconds\n\n", elapsed);

    t = clock();
    printf("Iteration (Addition sequence): %lu\n", fib_sequence(n, false));
    t = clock() - t;
    elapsed = (double)t / CLOCKS_PER_SEC;
    printf("took %f seconds\n\n", elapsed);

    HASH_MAP_INIT(mp);

    t = clock();
    printf("Recursive (Optimized): %lu\n", fib_recursive_optimized(n, &mp));
    t = clock() - t;
    elapsed = (double)t / CLOCKS_PER_SEC;
    printf("took %f seconds\n\n", elapsed);

    t = clock();
    printf("Recursive (Optimized + Cache): %lu\n",
           fib_recursive_optimized(n, &mp));
    t = clock() - t;
    elapsed = (double)t / CLOCKS_PER_SEC;
    printf("took %f seconds\n\n", elapsed);

    mp.hm_free(&mp);

    t = clock();
    printf("Recursive (Unoptimized): %lu\n", fib_recursive(n));
    t = clock() - t;
    elapsed = (double)t / CLOCKS_PER_SEC;
    printf("took %f seconds\n\n", elapsed);

    return 0;
}
