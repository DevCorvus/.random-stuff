import time


def count_paths(grid, y=0, x=0):
    y_length = len(grid) - 1
    x_length = len(grid[0]) - 1

    if y == y_length and x == x_length:
        return 1

    if y > y_length or x > x_length or grid[y][x] == 2:
        return 0

    return count_paths(grid, y + 1, x) + count_paths(grid, y, x + 1)


def count_paths_with_memo(grid, y=0, x=0, memo={}):
    y_length = len(grid) - 1
    x_length = len(grid[0]) - 1

    if y == y_length and x == x_length:
        return 1

    if y > y_length or x > x_length or grid[y][x] == 2:
        return 0

    key = f"{y}:{x}"

    if memo.get(key):
        return memo[key]

    result = count_paths_with_memo(grid, y + 1, x, memo) + count_paths_with_memo(
        grid, y, x + 1, memo
    )
    memo[key] = result
    return result


# This works summing the composition of smaller grids (walls are not considered)
def count_paths_math_alternative(y, x):
    if y == 1 or x == 1:
        return 1

    return count_paths_math_alternative(y - 1, x) + count_paths_math_alternative(
        y, x - 1
    )


grid = [
    [0, 0, 0],
    [0, 0, 0],
    [0, 0, 0],
]

t = time.process_time()
print("No Memo:", count_paths(grid))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", count_paths_with_memo(grid))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Alternative:", count_paths_math_alternative(len(grid), len(grid[0])))
print("took {:f} seconds\n".format(time.process_time() - t))
