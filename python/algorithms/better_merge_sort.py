import math


def merge_sort(numbers):
    num_len = len(numbers)

    if num_len <= 1:
        return numbers

    mid = math.floor(num_len / 2)
    return merge(merge_sort(numbers[mid:]), merge_sort(numbers[:mid]))


def merge(left, right):
    def _merge():
        while left and right:
            yield (left if left[0] <= right[0] else right).pop(0)

        yield from left
        yield from right

    return list(_merge())


numbers = [2, 4, 1, 5, 3]


print("Result:", merge_sort(numbers))
