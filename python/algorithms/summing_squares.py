import time
import math


def summing_squares(n):
    if n == 0:
        return 0

    min_squares = math.inf

    i = 1
    while i <= math.sqrt(n):
        square = i * i
        squares_count = 1 + summing_squares(n - square)

        if squares_count < min_squares:
            min_squares = squares_count

        i += 1

    return min_squares


def summing_squares_with_memo(n, memo={}):
    if n == 0:
        return 0

    min_squares = math.inf

    if memo.get(n):
        return memo[n]

    i = 1
    while i <= math.sqrt(n):
        square = i * i
        squares_count = 1 + summing_squares_with_memo(n - square, memo)

        if squares_count < min_squares:
            min_squares = squares_count

        i += 1

    memo[n] = min_squares
    return min_squares


n = 10

t = time.process_time()
print("No Memo:", summing_squares(n))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", summing_squares_with_memo(n))
print("took {:f} seconds".format(time.process_time() - t))
