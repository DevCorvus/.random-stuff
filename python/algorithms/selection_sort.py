def selection_sort(numbers):
    if len(numbers) <= 1:
        return numbers

    out = []

    while len(numbers):
        min = None
        for n in numbers:
            if min != None:
                if n < min:
                    min = n
            else:
                min = n

        out.append(min)
        numbers.remove(min)

    return out


def selection_sort_alternative(numbers):
    if len(numbers) <= 1:
        return numbers

    out = []

    for _ in range(len(numbers)):
        index_to_move = find_min_number_index(numbers)
        out.append(numbers.pop(index_to_move))

    return out


def find_min_number_index(numbers):
    min_index = 0
    for i in range(1, len(numbers)):
        if numbers[i] < numbers[min_index]:
            min_index = i

    return min_index


print(selection_sort_alternative([3, 1, 2]))
