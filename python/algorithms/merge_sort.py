import math


def merge_sort(numbers: list) -> list:
    num_len = len(numbers)

    if num_len <= 1:
        return numbers.copy()

    mid = math.floor(num_len / 2)
    return merge(merge_sort(numbers[:mid]), merge_sort(numbers[mid:]))


def merge(left_half: list, right_half: list) -> list:
    left_len = len(left_half)
    right_len = len(right_half)

    out = []

    left_idx = 0
    right_idx = 0

    while left_idx < left_len and right_idx < right_len:
        if left_half[left_idx] < right_half[right_idx]:
            out.append(left_half[left_idx])
            left_idx += 1
        else:
            out.append(right_half[right_idx])
            right_idx += 1

    while left_idx < left_len:
        out.append(left_half[left_idx])
        left_idx += 1

    while right_idx < right_len:
        out.append(right_half[right_idx])
        right_idx += 1

    return out


numbers = [4, -1, 9, 6, 2]
print(merge_sort(numbers))
