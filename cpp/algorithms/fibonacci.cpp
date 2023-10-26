#include <ctime>
#include <iostream>
#include <unordered_map>

/* long fib(uint n, std::unordered_map<uint, long> &cache) { */
long fib(uint n) {
    static std::unordered_map<uint, long> cache;

    if (n <= 1) {
        return n;
    }

    if (cache.find(n) != cache.end()) {
        return cache[n];
    } else {
        long result = fib(n - 1) + fib(n - 2);
        cache[n] = result;
        return result;
    }
}

int main(void) {
    /* std::unordered_map<uint, long> cache; */
    /* long result = fib(40, cache); */

    clock_t t;
    double elapsed;

    t = clock();
    std::cout << "Recursive (Optimized): " << fib(40) << std::endl;
    t = clock() - t;
    elapsed = (double)t / CLOCKS_PER_SEC;
    printf("took %f seconds\n\n", elapsed);

    return 0;
}
