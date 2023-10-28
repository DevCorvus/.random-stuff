import time


def non_adjacent_sum(numbers, i=0):
    if i >= len(numbers):
        return 0

    current = numbers[i] + non_adjacent_sum(numbers, i + 2)
    next = non_adjacent_sum(numbers, i + 1)

    return max(current, next)


def non_adjacent_sum_with_memo(numbers, i=0, memo={}):
    if i >= len(numbers):
        return 0

    if memo.get(i):
        return memo[i]

    curr_non_adjacent_sum = numbers[i] + non_adjacent_sum_with_memo(
        numbers, i + 2, memo
    )
    next_non_adjacent_sum = non_adjacent_sum_with_memo(numbers, i + 1, memo)

    highest = max(curr_non_adjacent_sum, next_non_adjacent_sum)
    memo[i] = highest
    return highest


numbers = [2, 4, 5, 12, 7]

t = time.process_time()
print("No Memo:", non_adjacent_sum(numbers))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", non_adjacent_sum_with_memo(numbers))
print("took {:f} seconds".format(time.process_time() - t))
