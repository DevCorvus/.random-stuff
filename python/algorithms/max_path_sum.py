import time
import math


def max_path_sum(grid, y=0, x=0):
    y_length = len(grid) - 1
    x_length = len(grid[0]) - 1

    if y > y_length or x > x_length:
        return -math.inf

    if y == y_length and x == x_length:
        return grid[y][x]

    return grid[y][x] + max(max_path_sum(grid, y + 1, x), max_path_sum(grid, y, x + 1))


def max_path_sum_with_memo(grid, y=0, x=0, memo={}):
    y_length = len(grid) - 1
    x_length = len(grid[0]) - 1

    if y > y_length or x > x_length:
        return -math.inf

    if y == y_length and x == x_length:
        return grid[y][x]

    key = f"{y}:{x}"

    if memo.get(key):
        return memo[key]

    sum = grid[y][x] + max(
        max_path_sum_with_memo(grid, y + 1, x, memo),
        max_path_sum_with_memo(grid, y, x + 1, memo),
    )
    memo[key] = sum
    return sum


grid = [[1, 3, 12], [5, 6, 2]]

t = time.process_time()
print("No Memo:", max_path_sum(grid))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", max_path_sum_with_memo(grid))
print("took {:f} seconds".format(time.process_time() - t))
