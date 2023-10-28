import time


# O(n) -> Linear time complexity
def fib_recursive_optimized(n, cache):
    if n <= 1:
        return n

    result = None

    if cache.get(n):
        result = cache[n]
    else:
        result = fib_recursive_optimized(n - 1, cache) + fib_recursive_optimized(
            n - 2, cache
        )
        cache[n] = result

    return result


# O(2^n) -> Exponential time complexity
def fib_recursive(n):
    if n <= 1:
        return n

    return fib_recursive(n - 1) + fib_recursive(n - 2)


# O(n) -> Linear time complexity
def fib(n):
    if n <= 1:
        return n

    a = 0
    b = 1
    total = 0

    for n in range(2, n + 1):
        total = a + b

        a = b
        b = total

    return total


# O(n) -> Linear time complexity
def fib_sequence(n):
    if n <= 1:
        return n

    sequence = [0, 1]

    for n in range(2, n + 1):
        sequence.append(sequence[n - 1] + sequence[n - 2])

    return sequence[n]


print("Fibonacci algorithms:\n")

n = 40

t = time.process_time()
print("Iteration (Total sum):", fib(n))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Iteration (Addition Sequence):", fib_sequence(n))
print("took {:f} seconds\n".format(time.process_time() - t))

cache = {}

t = time.process_time()
print("Recursive (Optimized):", fib_recursive_optimized(n, cache))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Recursive (Optimized + Cache):", fib_recursive_optimized(n, cache))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Recursive (Unoptimized):", fib_recursive(n))
print("took {:f} seconds\n".format(time.process_time() - t))
