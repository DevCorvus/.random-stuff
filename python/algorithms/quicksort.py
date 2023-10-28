def quicksort(numbers):
    if len(numbers) <= 1:
        return numbers

    less_than_pivot = []
    greater_than_pivot = []
    pivot = numbers[0]

    for n in numbers[1:]:
        if n <= pivot:
            less_than_pivot.append(n)
        else:
            greater_than_pivot.append(n)

    return quicksort(less_than_pivot) + [pivot] + quicksort(greater_than_pivot)


print(quicksort([3, 1, 2]))
