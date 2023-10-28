import math


def binary_search(numbers, target):
    print(numbers)

    if len(numbers) == 0:
        return False

    if len(numbers) == 1:
        if numbers[0] == target:
            return True
        else:
            return False

    mid = math.floor(len(numbers) / 2)
    number_at_mid = numbers[mid]

    if number_at_mid == target:
        return True

    if target < number_at_mid:
        return binary_search(numbers[:mid], target)
    else:
        return binary_search(numbers[mid:], target)


numbers = [1, 2, 3]
print(binary_search(numbers, 4))
